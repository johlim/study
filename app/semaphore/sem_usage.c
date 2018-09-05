#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <semaphore.h>
#include <pthread.h>

#define SEMKEY	(key_t)0111

void testsem(int semid);
void p(int semid);
void v(int semid);

sem_t           SemUpdate;                  // for pending and resume

int main(int argc, char ** argv[], char ** envp[])
{
    sem_init(&SemUpdate, 1, 0); // share, value 0

    sem_post(&SemUpdate);

    sem_wait(&SemUpdate);

    sem_destroy(&SemUpdate);

    return 0;
}
