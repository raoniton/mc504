# MC504 - Sistemas Operacionais 
<br>

# Projeto Multithread &nbsp;&nbsp;&nbsp;![C](https://img.shields.io/badge/language-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white) ![Pthread](https://img.shields.io/badge/-pthread-%2300AEFF.svg?style=for-the-badge) ![Ncurses](https://img.shields.io/badge/-ncurses-lightgray?style=for-the-badge) ![Mach](https://img.shields.io/badge/-Mach/-FF4500?style=for-the-badge&logoColor=black)
O projeto multithread foi proposto na disciplina de Sistemas Operacionais, era necessário fazer um programa que utilizasse a biblioteca **pthread** e apresentasse uma forma de visualização animada da execução do programa e não somente printar as saídas.

Esse projeto multithread simula de forma simplicaficada o funcionamento de um aeroporto, que recebe vários aviões que realizam pousos e decolagens.

As pthreads criadas representam os aviões e os recursos disputados pelas pthreads(aviões), são:
- as vagas(podemos ter várias vagas).
- a pista(só temos uma pista).
- e janela de log(só temos uma janela de log).

## Elementos importantes

#### Organização
~~~
──/aeroporto                         <- raiz do projeto
       ├── Makefile                  <- o makefile compila ambos programas o aeroporto com exibição e sem.
       ├── aeroporto.c               <- programa principal que contem a animação do funcionamento.
       ├── aeroportoSemExibicao.c    <- programa simplificado somente com as saídas no terminal.
       ├── exibicao.h                <- header com as definições, inclusões e assinaturas das funções.
       ├── exibicao.c                <- funções da exibição que faz uso da biblioteca NCURSES.
       └── README.md                 <- this.
~~~
#### Bibliotecas utilizadas:
~~~
  #include <ncurses.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <pthred.h>
  #include <mach/semaphore.h>
  #include <mach/mach_init.h>
  #include <mach/task.h>

~~~

#### Semaphore.h | mach/semaphore.h
Infelizmente não foi possível utilizar a biblioteca semaphore.h e assim utilizar o sem_init, sem_wait, sem_post, etc., isso porque o projeto foi feito numa máquina mac OS, e embora haja os protótipos e assinaturas das funções da semaphore.h, não há implementação. Com isso a solução foi utilizar outro semaforo, os semaforos da biblioteca mach/semaphore.h tem funcionamento diferente, mas ainda sim é um entrega um semáforo e dessa forma, foi possível contornar esse problema. 

## Execução
utilizando o makefile, o programa é compilado.
É possível alterar o número de vagas e de aviões no arquivo **#######**, optei por deixar hard coded. 

### ./aeroporto 
A tela estará dividida em algumas partes, as partes mais importantes são a pista, as vagas e a janela de log.
1. O avião percebe que há uma vaga -> Fica aguardando para pousar. 
2. Uma mensagem é escrita na janela de log "Aeronave ID aguardando decolagem".
3. Assim que o avião consegue o direito de pousar, uma breve animação de um avião pousando na pista é feita.
4. Uma mensagem é escrita na janela de log "Aeronave ID pousou >>".
5. Um avião é denhado em uma vaga.
6. Se outros aviões estiverem pousando os passos acima se repetem, enquanto tiver vaga, até que algum avião pessa para decolar.
7. Uma mensagem é escrita na janela de log "Aeronave ID aguardando decolagem".
8. Assim que a pista estiver e o avião conseguir o direito de pousar, umar breve animação de um avião delocando é feita.
9. Uma mensagem é escrita, na janela de log "Aeronave ID decolou <<".

### ./aeroportoSemAnimacao
Segue os mesmo passos acima, com a diferença de que sua implementação não tem os Semaforos de vagasAnimacao e log, consequentemente não tem animação.
Apresenta apenas as saídas, mas também é interessante de ver.








