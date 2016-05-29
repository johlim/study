#include <sys/types.h>
#include <sys/times.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main1(void)
{

    printf("PID : %d\n", (int) getpid());
    printf("PGRP : %d\n", (int) getpgrp());
    printf("PGID(0) : %d\n", (int) getpgid(0));
    printf("PGID(6856) : %d\n", (int) getpgid(6856));
     printf("SID : %d\n", (int) getsid(0));

    return 0;
}
#define CLK_TCK 1000000000
int main3(void)
{

    int i;
    time_t t;
    struct tms mytms;
    clock_t t1 , t2;

    if ((t1 = time(&mytms))== -1)
    {
        perror("time 1");
        exit(1);
    }

    for(i=0; i < 999999; i++)
    time(&t);

    if ((t1 = time(&mytms))== -1)
    {
        perror("times 2");
        exit(1);
    }

    printf("Real time : %.lf sec\n" ,(double)(t2-t1)/CLK_TCK);
    printf("User time : %.lf sec\n" ,(double)mytms.tms_utime/CLK_TCK);
    printf("System time : %.lf sec\n" ,(double)mytms.tms_stime/CLK_TCK);
}
void cleanup1(void)
{
    printf("cleanup1");
}
    int main2(void)
{
    pid_t pid;
    char * argv[3];
    char * envp[2];
    int status;

    argv[0]="ls";
    argv[1]="-a";
    argv[2]=NULL;


    switch(pid =fork())
    {

        case -1 : perror("fork");
        exit(1);
        break;
        case 0 :
        printf (" child %d %d\n", getpid(), getppid());
        atexit(cleanup1);
        sleep(10);
        exit(2);
        break;
        default :
        printf("parnet %d %d %d\n", getpid(), getppid(), pid);

        break;
    }
    #if 0
    while(wait(&status) != pid) // child pid 는 null or parent pid 는 child process id
    continue;
    #endif

    if (pid != NULL)
    {
        printf("waitpid\n");
        waitpid(pid, &status,__WALL);

    }

    printf("End of fork\n");
    printf("Child process %d\n",
           status >> 8);



    return 0;
}

int main0(void)
{
    char * argv[3];
    char * envp[2];

    argv[0]="ls";
    argv[1]="-a";
    argv[2]=NULL;

    //if (execlp("ls", "ls", "-a", (char*)NULL)== -1)
    if (execve("/bin/ls", argv, envp)== -1)
    {
        perror("execvp");
        exit(1);

;    }
    printf("-->After exec function\n");
}

int main4(void)
{
    char devmmc[]="/etc/mtab";
    char sbuf[BUFSIZ];

    FILE * fp;

    fp = fopen(devmmc, "r");

    while(fgets(sbuf, BUFSIZ, fp) != NULL)
    {
        //printf("%s\n",sbuf);
        if (strncmp(sbuf,"/dev/sdc1",8) == 0 )
        printf("%s Found MMC Device \n",sbuf);

    }
    fclose(fp);

}
