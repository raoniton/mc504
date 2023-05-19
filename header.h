#ifdef LINUX

    #include <semaphore.h>
    #define SEM_T sem_t
    #define SEM_INIT(SEM,V,INITIAL)         sem_init(&SEM, V, INITIAL);
    #define SEM_WAIT(SEM)                   sem_wait(&SEM);
    #define SEM_POST(SEM)                   sem_post(&SEM);
    #define SEM_DESTROY(SEM)                sem_destroy(&SEM);
 //   #define  _REENTRANT

#endif

#ifdef __APPLE__

    #include <mach/mach_init.h>
    #include <mach/task.h>
    #include <mach/semaphore.h>
    //#define  _REENTRANT
    #define SEM_T semaphore_t

    /*
    SYNC_POLICY_FIFO		    0x0  - essa funcionou bem juntamente com a exibicao
    SYNC_POLICY_FIXED_PRIORITY	0x1  - nao funcionou bem com a exibicao
    SYNC_POLICY_REVERSED		0x2  - essa funcionou bem juntamente com a exibicao
    SYNC_POLICY_ORDER_MASK		0x3  - nao funcionou bem com a exibicao
    SYNC_POLICY_LIFO                 - essa funcionou bem juntamente com a exibicao 
                                                                                    |
                                                                                    v               */
    #define SEM_INIT(SEM,V,INITIAL)         semaphore_create(current_task(), &SEM, SYNC_POLICY_LIFO, INITIAL);
    #define SEM_WAIT(SEM)                   semaphore_wait(SEM);
    #define SEM_POST(SEM)                   semaphore_signal(SEM);
    #define SEM_DESTROY(SEM)                semaphore_destroy(current_task(),  SEM);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_PTHREADS 5
#define N_VAGAS 4       //dependendo do numero de vagas, o programa pode nao rodar, devido ao tamanho do termininal necessario, 
                        //se isso acontecer, reduza o numero de vagas
                        