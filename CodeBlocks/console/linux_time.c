#include <time.h>

clockid_t clocks[] = {
CLOCK_REALTIME,
CLOCK_MONOTONIC,
CLOCK_PROCESS_CPUTIME_ID,
CLOCK_THREAD_CPUTIME_ID,
(clockid_t) -1};

extern int clock_getres (clockid_t __clock_id, struct timespec *__res);
int main(void)
{
int i;
for (i=0; clocks[i] != (clockid_t) -1; i++)
{
    struct timespec res;
    int ret;

    ret = clock_getres(clocks[i], &res);

    if (ret)
    perror("clock_getres");
    else
    printf("clock %d, sec %ld, nsec %ld\n", clocks[i], res.tv_sec, res.tv_nsec);
}
}

