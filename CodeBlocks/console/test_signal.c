#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <fcntl.h>

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int child(void)
{
        printf("Before SIGCONT Signal to parent.\n");

        kill(getppid(), SIGCONT);


        kill(getppid(), SIGQUIT);

        printf("Before SIGQUIT Signal to self.\n");

        kill(getpid(), SIGQUIT);

        printf("After SIGQUIT Signal to self.\n");


}

void sig_handler(int signo)
{
    void (*hand) (int);
#if 0
    hand = signal(SIGINT, sig_handler);
    if (hand == SIG_ERR)
        perror("signal");
 #endif

    psignal(signo, "Received Signal");

    sleep(5);

    psignal(signo, "After Sleep");

}


int main5(void)
{
    void (*hand)(int);
    int pid=0;
    struct sigaction act;

    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags =SA_RESETHAND;// SA_NODEFER;
    act.sa_handler = sig_handler;


    if (sigaction(SIGINT, &act, (struct sigaction *)NULL)<0)
    {
        perror("sigaction");
        exit(1);
    }

    if (sigismember(&act.sa_mask, SIGQUIT))
    printf("SIGQUIT is masked\n");

    printf("** before pattern : \n");
    //pause();
    while(1);
    printf("** after pattern : \n");

    return 0;
}

static i=0;

void handler(int signo) {
    char * s;
s = strsignal(signo);
i++;
printf("Received Signal : %s(%d)\n",s, i);
}

int main4(void)
{
    if (sigset(SIGINT, handler)==SIG_ERR)
    perror("sigset");

    if (sigset(SIGQUIT, handler)==SIG_ERR)
    perror("sigset");

//    sighold(SIGINT);
//    sighold(SIGQUIT);

    pause();

    return 0;
}

int main3(void)
{
    sigset_t new;

    sigemptyset(&new);
    sigaddset(&new, SIGINT);
    sigaddset(&new, SIGQUIT);
    sigprocmask(SIG_BLOCK, &new, (sigset_t *) NULL);

    printf("Block Signal\n");

    kill(getpid(), SIGQUIT);

    printf("Un Block Signal\n");

    sigprocmask(SIG_UNBLOCK, &new, (sigset_t *) NULL);

    return 0;
}
int main2(void)
{

    struct itimerval it={0,};
    sigset_t new;
    if (sigset(SIGALRM, handler)==SIG_ERR)
    perror("sigset");

    sigfillset(&new);
    sigdelset(&new, SIGALRM);
    sigdelset(&new, SIGINT);

    //alarm(1);
    it.it_value.tv_sec  = 1;
    it.it_interval.tv_sec  = 2;

    setitimer(ITIMER_REAL, &it, NULL);

    sigprocmask(SIG_BLOCK, &new, (sigset_t *) NULL);
    //sigsuspend(&new);
    while(1){ sleep(1);}

    return 0;
}


int main_map(int argc, char * argv[])
{
    int fd;
    caddr_t addr;
    struct stat statbuf;
    int pid;

#if 1
    if (sigset(SIGUSR1, handler)==SIG_ERR)
    perror("sigset");
#endif

    //sigignore(SIGSEGV);

    if (argc < 2) exit(1);

    if (stat(argv[1], &statbuf)== -1)
    exit(1);

    if((fd = open(argv[1], O_RDWR)) ==  -1)
    exit(1);

    addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)0);

    if (addr == MAP_FAILED) exit(1);

    close(fd);

    printf("fork\n");
    switch(pid = fork())
    {
        case -1:

        break;
        case 0:
        printf("Child \n");
        addr[0]='x';
        kill(getppid(), SIGUSR1);

        exit(0);
        break;
        default :
        printf("Parent \n");
        sigpause(SIGUSR1);
        printf ("%s", addr);
        addr[1]='Y';
        printf ("%s", addr);
    }
    printf("switch \n");;
    return 0;
}
int main(int argc, char * argv[])
{
    int fd[2];
    pid_t pid;
    char buf[BUFSIZ];
    int len, status;

#if 1
    if (sigset(SIGUSR1, handler)==SIG_ERR)
    perror("sigset");
#endif

    if(pipe(fd) == -1) exit(1);


      printf("fork\n");
    switch(pid = fork())
    {
        case -1:

        break;
        case 0:
        printf("Child \n");
        write(fd[1], "Test Message\n", 14);
        close(fd[1]);



        exit(0);
        break;
        default :
        waitpid(pid, &status, 0);
        printf("Parent \n");
        len = read(fd[0], buf, 256);
        printf("%s", buf);
        close(fd[0]);
        break;
    }
    printf("switch \n");;
    return 0;
}
