/*
###############################################################################
#                   S.O. - SISTEMAS OPERACIONAIS - 1S_2023                    #
#                   PROFa:  ISLENE CALCIOLARI GARCIA                          #
#                   NOME:   RAONITON ADRIANO DA SILVA                         #
#                   RA:     186291                                            #
###############################################################################
*/

#include <pthread.h>
#include "header.h"

SEM_T vagas;                   
SEM_T pista;
int controleLogAero = 1;

void *aeroporto(void *id){
    int tipo;
    int pos;
    
    SEM_WAIT(vagas);            
        printf("  Aeronave %d aguardando pouso\n",*(int *)id);
    
        //PEDINDO AUTORIZACAO PARA POUSA
        sleep(1);

        SEM_WAIT(pista);
            srand( (unsigned)time(NULL) );
            tipo = rand()%2;            //tipo serve para desenhar o aviao na animacao, aviao grande, ou aviao pequeno    
            printf("  Aeronave %d pousou >>\n",*(int *)id);
            sleep(1);
        SEM_POST(pista);
    
        //TEMPO OCUPANDO UM VAGA NO AEROPORTO
        sleep(rand()%15);
        printf("  Aeronave %d aguardando decolagem\n",*(int *)id);
    
        //PEDINDO AUTORIZACAO PARA DECOLAR ANTES DE LIBERAR A VAGA
        usleep(1000000);
        SEM_WAIT(pista);
            //mvwprintw(win2, controleLogAero++,1, "Aeronave %d aguardando pouso", *(int *)id);
            printf("  Aeronave %d decolou <<\n",*(int *)id);
        SEM_POST(pista);
    
        free(id);                   //libero o ponteiro que aloquei na criacao das threads, servia para mostrar o id    
    SEM_POST(vagas);                //if you are on linux use: sem_post(&vagas);
    return NULL;
}



int main(){
    //DECLARACO DAS VARIAVEIS LOCAIS DA MAIN
    int i;
    void *p;

    //DECLARO AS PTHREADS - REPRESENTAM OS AVIOES
    pthread_t threads[N_PTHREADS];

    //INICIO OS SEMAFOROS
    SEM_INIT(vagas, 0, N_VAGAS);
    SEM_INIT(pista, 0, 1);

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
    
    printf("\n  ACABOU :)\n");
    
    //ENCERRO OS SEMAFOROS
    SEM_DESTROY(vagas);
    SEM_DESTROY(pista);
    return 0;
}

