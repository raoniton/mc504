#include "exibicao.h"

//Essa variavel controla o tempo da animacao de pouso e decolagem (em MILISSEGUNDOS), 
//quanto maior o valor, mais lenta eh a animacao
//quanto menor o valor, mais rapida eh a animacai
int tempoDePousoAnimacao = 55000;

/*
*  settingShowWindow - recebe as 3 janelas de apresentacao e o numero de vagas, e 
*  prepara o todo os espaco
*  win - representa a pista
*  win2 - janela onde os logs e saidas sao apresentados
*  win3 - representa as vagas
*/
void settingShowWindow(WINDOW *win, WINDOW *win2, WINDOW *win3[], WINDOW *programName, int n_vagas){
    mvwprintw(programName, 1, 47,  "AEROPORTO\n");
    wborder(programName, 0, 0, 0, 0, 0, 0, 0, 0);
    
    wborder(win, ' ', ' ', 0, 0, 0, 0, 0, 0);   //cololo 
    desenhaVagas(win3, n_vagas);                //aloca e desenha as vagas na tela
    box(win2, 0, 0);                            
    mvwprintw(win,  1, 0, "  =======       =======       =======       =======       =======");     //desenho da pista
    mvwprintw(win, 13, 0, "  =======       =======       =======       =======       =======");     //desenho da pista
    
    scrollok(win2, TRUE);                       //ativando o scrolling da janela de logs
    curs_set(FALSE);                            //para nao exibir o cursor

    atualizaTodasJanelas(win, win2, win3, programName, n_vagas);

}

/*
*   atualizaTodasJanelas 
*/
void atualizaTodasJanelas(WINDOW *win, WINDOW *win2, WINDOW *win3[], WINDOW *programName, int n_vagas){
  int i;
  refresh();
  wrefresh(win);
  wrefresh(win2);

  for( i=0; i < n_vagas; i++){
    wrefresh(win3[i]); 
  }

  wrefresh(programName);
  
}

/*
*   atualizaUmaVaga - apos limpar a vaga com a funcao clearVaga, eh preciso atualizar a 
*   janela para que na exibicao apareca a vaga vazia
*/
void atualizaUmaVaga(WINDOW *win){
    wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
    refresh();
    wrefresh(win); 
}

/*
*  desenhaVagas - funcao auxiliar da funcao settingShowWindow, recebe o vetor de janelas win e o numero de vagas,
*  desenha o numero de vagas definido no programa principal
*/
void desenhaVagas(WINDOW *win[], int n_vagas){
  int i=0, counter=0, posHorizontal = 0, posVertical = 18;
  printf("%d", n_vagas);
  
  for(i=0; i < n_vagas; i++){
    
    if(counter >= 6 ){
      counter=0;
      posHorizontal += -102;
      posVertical += 10;
      win[i] = newwin(10, 17, posVertical, posHorizontal);
      //mvwprintw(win[i], 1, 1, "%d", i);
      posHorizontal += 17;
   
    }else{
      win[i] = newwin(10, 17, posVertical, posHorizontal);
      //mvwprintw(win[i], 1, 1, "%d", i);
      posHorizontal+=17;
    }
    counter++;
    wborder(win[i], 0, 0, 0, 0, 0, 0, 0, 0);
    refresh();
    wrefresh(win[i]);
    
  }
}

/*
* verificaControleLogAero - recebe a janala de log, a posicao atual em y do texto, a mensagem e o id da thread que chamou
* controleLogAero eh um incremento na posicao y que vamos escrever na tela de log
* cada nova mensagem sera escrita na linha debaixo
*/
void verificaControleLogAero(WINDOW *win2, int *controleLogAero, char s[], void *id){
    wprintw(win2,  s, *(int *)id);
    wmove(win2, (*controleLogAero)++, 1);
    wborder(win2, 0, 0, 0, 0, 0, 0, 0, 0);
    refresh();
    wrefresh(win2);
}

/*
*  verificaVagaVazia - verifica qual posicao esta vazia, serve apenas para realizar a visualizacao aviao 
*  ocupando a vaga. Retorna a posica da vaga vazia. Como temos um semaforo, sempre que essa funcao for chamada
*  havera alguma vaga vazia.
*/
int verificaVagaVazia(int controleVagasAnimacao[], int n_vagas){
    int i;
    for(i=0; i< n_vagas; i++){
        if(controleVagasAnimacao[i] == 0)
            return i;
    }
    exit(1);
    
}

/*
*  clearFinalPista - escreve espacos na posicao que o aviao para quando chega ao final da pista(POUSO)
*/
void clearFinalPista(WINDOW *win){
  int i;
  for(i=0; i < 9; i++){
    mvwprintw(win, i+3, 44, "                     ");
  }
  refresh();
  wrefresh(win);
}

/*
*  clearInicioPista - escreve espacos na posicao que o aviao para quando chega ao inicio da pista(DECOLAGEM)
*/
void clearInicioPista(WINDOW *win){
  int i;
  for(i=0; i < 9; i++){
    mvwprintw(win, i+3, 1, "                     ");
  }
  refresh();
  wrefresh(win);
}

/*
*   clearVaga - escreve espacos na vaga que o aviao acabou de liberar e atualiza para realmente mostrar 
*   na exibicao
*/
void clearVaga(WINDOW *win){
  int i;
  for(i=0; i < 8; i++){
    mvwprintw(win, i+1, 1, "               ");
  }
  //wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
  refresh();
  wrefresh(win); 
}


/*
*   desenhaNaVaga - tem um nome intuitivo haha, apos o aviao pousar, eh desenhado na vaga um aviao de acordo
ª   com o tipo de aviao
*/
void desenhaNaVaga(WINDOW *win, int tipo, int *id){
  int y=1, x=0;
  if(tipo == 0){
    mvwprintw(win, x+1, y, "    @     @    ");
    mvwprintw(win, x+2, y, "      @@@      ");
    mvwprintw(win, x+3, y, " @     @     @ ");
    mvwprintw(win, x+4, y, "  @@   @   @@  ");
    mvwprintw(win, x+5, y, "    @| %d |@   ", *(int *)id);
    mvwprintw(win, x+6, y, "     @@@@@     ");
    mvwprintw(win, x+7, y, "       @       ");
    mvwprintw(win, x+8, y, "       @       ");
  }else if(tipo == 1){
    mvwprintw(win, x+2, y+1, "    @@ @@    ");
    mvwprintw(win, x+3, y+1, "      @      ");
    mvwprintw(win, x+4, y+1, "      @      ");
    mvwprintw(win, x+5, y+1, " @@@@@@@@@@@ ");
    mvwprintw(win, x+6, y+1, " @@@| %d |@@@ ", *(int *)id);
    mvwprintw(win, x+7, y+1, "      @      ");
    mvwprintw(win, x+8, y+1, "      @      ");
  }
  atualizaUmaVaga(win);
}

/*
*   desenhaPouso - eh responsavel por simular o pouso do aviao na pista, o objeto eh printado incrementando 
*   a posicao da coluna que ele esta, do inicio ate o fim da pista
*   pousos sao da esquerda para a direita
*/
void desenhaPouso(WINDOW *win, int tipo, int *id){
  int y, x;
  if(tipo == 0){
    y=0;
    x=3;
    //char c[22] = "   @@@@@@| 01 |@@@@@@";
    while(y <44){
      mvwprintw(win, x+0, y, "      @              \n");
      mvwprintw(win, x+1, y, "       @@            \n");
      mvwprintw(win, x+2, y, " @      @@@          \n");
      mvwprintw(win, x+3, y, "  @@     @@@@@       \n");
      mvwprintw(win, x+4, y, "   @@@@@@| %d |@@@@@@\n", *(int *)id);
      mvwprintw(win, x+5, y, "  @@     @@@@@       \n");
      mvwprintw(win, x+6, y, " @      @@@          \n");
      mvwprintw(win, x+7, y, "       @@            \n");
      mvwprintw(win, x+8, y, "      @              \n");
      refresh();
      wrefresh(win);
      usleep(tempoDePousoAnimacao);
      y++;
      
    }
  }else if(tipo == 1){
    y=0;
    x=4;
    while(y < 49){
      mvwprintw(win, x+0, y, "       @@@@      \n");
      mvwprintw(win, x+1, y, " @@    @@@@      \n");
      mvwprintw(win, x+2, y, " @@    @@@@      \n");
      mvwprintw(win, x+3, y, "  @@@@| %d |@@@@ \n", *(int *)id);
      mvwprintw(win, x+4, y, " @@    @@@@      \n");
      mvwprintw(win, x+5, y, " @@    @@@@      \n");
      mvwprintw(win, x+6, y, "       @@@@      \n");
      refresh();
      wrefresh(win);
      usleep(tempoDePousoAnimacao);
      y++;
    }
  }
  //esse usleep eh para dar tempo de ver o aviao parado no fim da pista
  usleep(800000);
  clearFinalPista(win);
  refresh();
  wrefresh(win);
}

/*
*   desenhaDecolagem - eh responsavel por simular a decolagem do aviao na pista, o objeto eh printado incrementando 
*   a posicao da coluna que ele esta, do fim ate o inicio da pista.
*   Decolagens sao da direita para a esquerda
*/
void desenhaDecolagem(WINDOW *win, int tipo, int *id){
  int y, x;
  if(tipo == 0){
    y=44;
    x=3;
    //char c[22] = "   @@@@@@| 01 |@@@@@@";
    while(y > 0){
      mvwprintw(win, x+0, y, "               @     \n");
      mvwprintw(win, x+1, y, "            @@       \n");
      mvwprintw(win, x+2, y, "          @@@      @ \n");
      mvwprintw(win, x+3, y, "       @@@@@     @@  \n");
      mvwprintw(win, x+4, y, "@@@@@@| %d |@@@@@@   \n", *(int *)id);
      mvwprintw(win, x+5, y, "       @@@@@     @@  \n");
      mvwprintw(win, x+6, y, "          @@@      @ \n");
      mvwprintw(win, x+7, y, "            @@       \n");
      mvwprintw(win, x+8, y, "              @      \n");
      refresh();
      wrefresh(win);
      usleep(tempoDePousoAnimacao);
      y--;
      
    }
  }else if(tipo == 1){
    y=49;
    x=4;
    while(y > 0){
      mvwprintw(win, x+0, y, "     @@@@       \n");
      mvwprintw(win, x+1, y, "     @@@@    @@ \n");
      mvwprintw(win, x+2, y, "     @@@@    @@ \n");
      mvwprintw(win, x+3, y, "@@@@| %d |@@@@  \n", *(int *)id);
      mvwprintw(win, x+4, y, "     @@@@    @@ \n");
      mvwprintw(win, x+5, y, "     @@@@    @@ \n");
      mvwprintw(win, x+6, y, "     @@@@       \n");
      refresh();
      wrefresh(win);
      usleep(tempoDePousoAnimacao);
      y--;
    }
  }
  usleep(800000);
  clearInicioPista(win);
  refresh();
  wrefresh(win);
}