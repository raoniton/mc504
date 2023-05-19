/*
###############################################################################
#                   S.O. - SISTEMAS OPERACIONAIS - 1S_2023                    #
#                   PROFa:  ISLENE CALCIOLARI GARCIA                          #
#                   NOME:   RAONITON ADRIANO DA SILVA                         #
#                   RA:     186291                                            #
###############################################################################
*/

#include <pthread.h>
#include "exibicao.h"
#include "header.h"

//#define N_PTHREADS 5
//#define N_VAGAS 4       //dependendo do numero de vagas, o programa pode nao rodar, devido ao tamanho do termininal necessario, 
//                        //se isso acontecer, reduza o numero de vagas


SEM_T vagas;                   
SEM_T pista;
SEM_T logAero;
SEM_T vagasAnimacao;
WINDOW *programName;
WINDOW *win;
WINDOW *win2;
WINDOW *win3[N_VAGAS];  
int controleLogAero = 1;
int *controleVagasAnimacao;

void *aeroporto(void *id){
    int tipo;
    int pos;
    
    SEM_WAIT(vagas);            
        SEM_WAIT(logAero);
            verificaControleLogAero(win2, &controleLogAero, "  Aeronave %d aguardando pouso\n",id);
        SEM_POST(logAero);
    
        //PEDINDO AUTORIZACAO PARA POUSA
        sleep(1);
        SEM_WAIT(pista);
            
            SEM_WAIT(logAero);
                srand( (unsigned)time(NULL) );
                tipo = rand()%2;            //tipo serve para desenhar o aviao na animacao, aviao grande, ou aviao pequeno    
                
                desenhaPouso(win, tipo, id);
                verificaControleLogAero(win2, &controleLogAero, "  Aeronave %d pousou >>\n",id);
                SEM_WAIT(vagasAnimacao);
                    pos = verificaVagaVazia(controleVagasAnimacao, N_VAGAS);
                    controleVagasAnimacao[pos] = 1;
                    desenhaNaVaga(win3[pos], tipo, id);
                SEM_POST(vagasAnimacao);
                sleep(1);
            SEM_POST(logAero);
        
            
        SEM_POST(pista);
        
        //TEMPO OCUPANDO UM VAGA NO AEROPORTO
        sleep(rand()%15);
        
        SEM_WAIT(logAero);
            verificaControleLogAero(win2, &controleLogAero, "  Aeronave %d aguardando decolagem\n",id);
        SEM_POST(logAero);
        
        //PEDINDO AUTORIZACAO PARA DECOLAR ANTES DE LIBERAR A VAGA
        usleep(1000000);
        SEM_WAIT(pista);
            SEM_WAIT(logAero);
                //mvwprintw(win2, controleLogAero++,1, "Aeronave %d aguardando pouso", *(int *)id);
                verificaControleLogAero(win2, &controleLogAero,"  Aeronave %d decolou <<\n",id);
                SEM_WAIT(vagasAnimacao);
                    controleVagasAnimacao[pos] = 0;
                    clearVaga(win3[pos]);
                    desenhaDecolagem(win, tipo, id);
                SEM_POST(vagasAnimacao);
            SEM_POST(logAero);
        SEM_POST(pista);
        
    free(id);                   //libero o ponteiro que aloquei na criacao das threads, servia para mostrar o id    
    SEM_POST(vagas);            //if you are on linux use: sem_post(&vagas);
    return NULL;
}



int main(){
    //DECLARACO DAS VARIAVEIS LOCAIS DA MAIN
    int i, heigh, width, novaHeight=28, novaWidth;
    void *p;

    //DECLARO AS PTHREADS - REPRESENTAM OS AVIOES
    pthread_t threads[N_PTHREADS];

    //INICIO OS SEMAFOROS
    SEM_INIT(vagas, 0, N_VAGAS);
    SEM_INIT(pista, 0, 1);
    SEM_INIT(logAero, 0, 1);
    SEM_INIT(vagasAnimacao, 0, 1);

    //INICIALIZO O VETOR controleVagasAnimacao COM '0'(ZEROS), esse vetor eh controle de qual vaga desenhar o aviao estacionado
    controleVagasAnimacao = (int *)calloc(N_VAGAS, sizeof(int));
    
    //INICIALIZAO DA EXIBICAO UTILIZANDO NCURSES E PREPARACAO DOS ELEMENTOS DA TELA
    initscr();                                      //inicio o ncurses
    getmaxyx( stdscr, heigh, width );
    if(N_VAGAS > 6){
        novaHeight = 28 + 10*((int)N_VAGAS/6);
    }
    if(width != 105 || heigh != novaHeight){
        printf("\033[8;%d;105t", novaHeight);       //seto o tamanho do terminal para height: 30 e widht: 102 para correto funcionamento
        printf("O TAMANHO DA JANELA FOI CONFIGURADO, EXECUTE NOVAMENTE!");
        return 0;
    }
    
    programName = newwin(3,0,0,0);                  //essa janela exibe o nome AEROPORTO
    win = newwin(15, 68, 3 , 0);                    //essa janela representa a pista
    win2 = newwin(15, 0, 3, 68);                    //essa janela eh onde os logs e saidas sao apresentados
    settingShowWindow(win, win2, win3, programName, N_VAGAS);    //Aqui desenhamos as bordas das janelas
    wmove(win2,controleLogAero++, 1);               //coloca o cursor na posicao correta
    //usleep(250000);

    //CRIACAO DAS THREADS
    for(i=0; i < N_PTHREADS; i++){
        p = malloc(sizeof(int));
        *((int *)p) = i;
       if(pthread_create(&threads[i], NULL, &aeroporto, p)  != 0){
            perror("Erro na criacao da thread!");
       }
    }
    
    //JOIN PARA ASSEGURAR QUE O PROGRAMA NAO ENCERRE ANTES QUE AS THREADS FINALIZEM 
    for(i=0; i < N_PTHREADS; i++){
        if(pthread_join(threads[i], NULL) != 0)
            perror("Erro no join da thread!");
    }
    

    wprintw(win2,  "\n  ACABOU :)\n");
    wmove(win2,controleLogAero++, 1);
    wborder(win2, 0, 0, 0, 0, 0, 0, 0, 0);
    refresh();
    wrefresh(win2);
    
    werase(win);
    werase(win2);
    for(i=0; i < N_VAGAS; i++){
        werase(win3[i]);
    }
    werase(programName);
    free(controleVagasAnimacao);                    //libero da memoria
    erase();

    getchar();                                      //o programa aguarda um caracter para finalizar
    initscr();
    endwin();                                       //finalizo o ncurses
    
    //printf("%d", isendwin());
    
    
    //ENCERRO OS SEMAFOROS
    SEM_DESTROY(vagas);
    SEM_DESTROY(pista);
    SEM_DESTROY(logAero);
    SEM_DESTROY(vagasAnimacao);
    return 0;
}

