#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sched.h>
#include <errno.h>

using namespace std;

int error_callback(void)
{
    return false;
}
int main()
{
    cout << "Hello world!" << endl;

    cpu_set_t set={0,};
    int ret, i;

    CPU_ZERO(&set);
    CPU_SET(1, &set);
    CPU_CLR(0, &set);

    ret = sched_setaffinity(0, sizeof(cpu_set_t), &set);

    if (ret == -1)
    perror("sched_setaffinity");
   // atexit(error_callback);

    for(i=0;i<5;i++)
    {
        int cpu;
        cpu = CPU_ISSET(i, &set);
        printf("cpu=%i is %s\n", i, cpu ?"set":"unset");
    }

    printf("errno : %d", errno);

    daemon(1,0);
    while(1)
    msleep(100);
    return 0;
}
