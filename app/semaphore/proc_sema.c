#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
// stdc
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd, i,count=0,nloop=10,zero=0,*ptr;
    sem_t mutex;
    ////
    fd = open("log.txt",O_RDWR|O_CREAT,S_IRWXU);
    write(fd,&zero,sizeof(int));
    ptr = mmap(NULL,sizeof(int),PROT_READ |PROT_WRITE,MAP_SHARED,fd,0);
    close(fd);
    ////
    if( sem_init(&mutex,1,1) < 0)
    {
        perror("semaphore initilization");
        exit(0);
    }
    if (fork() == 0) { /* child process*/
        for (i = 0; i < nloop; i++) {
            sem_wait(&mutex);
            printf("child: %dn", (*ptr)++);
            sem_post(&mutex);
        }
        exit(0);
    }

    for (i = 0; i < nloop; i++) {
        sem_wait(&mutex);
        printf("parent: %dn", (*ptr)++);
        sem_post(&mutex);
    }
    exit(0);
}

