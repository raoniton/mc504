#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//PROTOTIPOS
void settingShowWindow(WINDOW *win, WINDOW *win2, WINDOW *win3[], WINDOW *programName, int n_vagas);
void verificaControleLogAero(WINDOW *win2, int *controleLogAero, char s[], void *id);
int verificaVagaVazia(int controleVagasAnimacao[], int n_vagas);
void clearFinalPista(WINDOW *win);
void clearFinalPista(WINDOW *win);
void clearInicioPista(WINDOW *win);
void clearVaga(WINDOW *win);
void clearLogWindow(WINDOW *win);
void desenhaVagas(WINDOW *win[], int n_vagas);
void atualizaUmaVaga(WINDOW *win);
void atualizaVagas(WINDOW *win[], int n_vagas);
void desenhaNaVaga(WINDOW *win, int tipo, int *id);
void desenhaPouso(WINDOW *win, int tipo, int *id);
void desenhaDecolagem(WINDOW *win, int tipo, int *id);
void atualizaTodasJanelas(WINDOW *win, WINDOW *win2, WINDOW *win3[], WINDOW *programName, int n_vagas);

