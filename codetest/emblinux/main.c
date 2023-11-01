#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "src/common_inc.h"
int fd;

int memopen(void)
{

    fd = open("/dev/mem", O_RDWR);
    if (fd < 0)
    {
        perror("dev/mem Faild \n");
        exit(1);
        return -1;
    }
    else
    {
        perror("dev/mem success \n");
        
        return 0;
    }

}
int main()
{
    printf("run as root\n");
    // printf("open /dev/mem, O_RDWR");
    // memopen();
    // return close(fd);
    module_call(1);
    sub_module_call(1);
}
