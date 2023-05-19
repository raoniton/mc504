CC = gcc

all:
	$(CC) aeroporto.c exibicao.c -o aeroporto -pthread -lncurses
	$(CC) aeroportoSemAnimacao.c -o aeroportoSemAnimacao -pthread