#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int fd;

int memopen(void)
{

    fd = open("/dev/mem", O_RDWR);
    if (fd < 0)
    {
        perror("dev/mem Faild \n");
    exit(1);
    }

    return 0;
}
int main()
{
    printf("Hello world!\n");

    memopen();


    close(fd);
    return 0;
}
