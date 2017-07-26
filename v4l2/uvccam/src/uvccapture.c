#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <linux/videodev2.h>

int main(int argc, char *argv[])
{
    char *device = "/dev/video0";
    struct v4l2_frmsizeenum size;
    int ret = 0, fd = 0;

    if (argc > 1)
        device = argv[1];

    printf(">> device name = %s \n", device);

    fd = open(device,O_RDONLY);
    if (-1 == fd) {
        fprintf(stderr, "open %s: %s\n", device, strerror(errno));
        exit(1);
    };

    size.index = 0;
    size.pixel_format = V4L2_PIX_FMT_YUYV;

    ret = ioctl (fd, VIDIOC_ENUM_FRAMESIZES, &size);
    if (ret < 0) {
        printf("ioctl error: VIDIOC_ENUM_FRAMESIZES\n");
        close(fd);
        exit(1);
    }   

    if (size.type == V4L2_FRMSIZE_TYPE_DISCRETE) {

        do {
            printf("witdth = %d    height = %d \n", size.discrete.width, size.discrete.height);
            size.index++;
        } while (ioctl (fd, VIDIOC_ENUM_FRAMESIZES, &size) == 0);

    } 

    close(fd);
    return 0;
}
