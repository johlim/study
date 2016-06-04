#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/time.h> //debug -> remove me
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <libudev.h>

#define ADD_FILTER "add"
#define REMOVE_FILTER "remove"
#define SUBSYSTEM_FILTER "block"
#define DEVTYPE_FILTER "disk"
#define ATTR_FILTER "ID_MODEL"
#define SD_ATTR_VALUE "SD_MMC"
#define ATTR_ADDED_DISK "UDISKS_PARTITION_TABLE" // attribute is available for "change" event when SD card is added (n/a when removed)

#ifndef bool
#define bool int
#endif
#ifndef false
#define false (0)
#endif
#ifndef true
#define true (1)
#endif



static bool isDeviceSD(struct udev_device *device); //checks if device is SD card (MMC)
static bool isDevPresent(struct udev *device); //checks if device is present (SD + added)
static bool isDeviceAdded(struct udev_device *device); //checks if device is added (presence of attribute ATTR_ADDED_DISK)
static void print_device(struct udev_device *device, const char *source); //for debugging -> remove me
static bool s_bSD_present;
int gcount;
int main_udev()
{
    struct udev *udev;
    struct udev_monitor *udev_monitor = NULL;
    fd_set readfds;
    s_bSD_present = false;

    udev = udev_new();
    if (udev == NULL)
    {
        printf("udev_new FAILED \n");
        return 1;
    }

    if( isDevPresent(udev) )
    {
        s_bSD_present = true;
        printf("+++SD is plugged in \n");
    }
    else
    {
        printf("---SD is not plugged in \n");
    }

    udev_monitor = udev_monitor_new_from_netlink(udev, "udev");
    if (udev_monitor == NULL) {
        printf("udev_monitor_new_from_netlink FAILED \n");
        return 1;
    }

    //add some filters
    if( udev_monitor_filter_add_match_subsystem_devtype(udev_monitor, SUBSYSTEM_FILTER, DEVTYPE_FILTER) < 0 )
    {
        printf("udev_monitor_filter_add_match_subsystem_devtype FAILED \n");
        return 1;
    }

    if (udev_monitor_enable_receiving(udev_monitor) < 0)
    {
        printf("udev_monitor_enable_receiving FAILED \n");
        return 1;
    }

    while (1) {
        printf("Polling for new data... \n");

        int fdcount = 0;

        FD_ZERO(&readfds);

        if (udev_monitor != NULL)
        {
            FD_SET(udev_monitor_get_fd(udev_monitor), &readfds);
        }

        fdcount = select(udev_monitor_get_fd(udev_monitor)+1, &readfds, NULL, NULL, NULL);
        if (fdcount < 0)
        {
            if (errno != EINTR)
                printf("Error receiving uevent message\n");
            continue;
        }

        if ((udev_monitor != NULL) && FD_ISSET(udev_monitor_get_fd(udev_monitor), &readfds))
        {
            struct udev_device *device;

            device = udev_monitor_receive_device(udev_monitor);
            if (device == NULL)
                continue;
            printf("SD %d ADD %d (%d) \n", isDeviceSD(device) , isDeviceAdded(device), gcount++);
            //check presence
            if( isDeviceSD(device) && isDeviceAdded(device) )
            {
                if(!s_bSD_present) //guard for double "change" events
                {
                    s_bSD_present = true;
                    printf("+++SD has been plugged in \n");
                }
            }
            else
            {

                if(s_bSD_present) //not needed -> just keeping consistency
                {
                    s_bSD_present = false;
                    printf("---SD has been removed \n");
                }
            }

            udev_device_unref(device);
        }
    }

    return 0;
}

static bool isDeviceSD(struct udev_device *device)
{
    bool retVal = false;
    struct udev_list_entry *list_entry = 0;
    struct udev_list_entry* model_entry = 0;

    list_entry = udev_device_get_properties_list_entry(device);
    model_entry = udev_list_entry_get_by_name(list_entry, ATTR_FILTER);
    if( 0 != model_entry )
    {
        const char* szModelValue = udev_list_entry_get_value(model_entry);
        if( strcmp( szModelValue, SD_ATTR_VALUE) == 0 )
        {
            //printf("Device is SD \n");
            retVal = true;

            //print_device(device, "UDEV");
        }
    }
    return retVal;
}

static bool isDeviceAdded(struct udev_device *device)
{
    bool retVal = false;
    struct udev_list_entry *list_entry = 0;
    struct udev_list_entry* added_disk_entry = 0;


    list_entry = udev_device_get_properties_list_entry(device);
    added_disk_entry = udev_list_entry_get_by_name(list_entry,/* "DEVNAME" */ ATTR_ADDED_DISK);
    if( 0 != added_disk_entry )
    {
        retVal = true;
    }
    return retVal;
}


static bool isDevPresent(struct udev *device)
{
    bool retVal = false;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *dev_list_entry;

    enumerate = udev_enumerate_new(device);
    udev_enumerate_add_match_subsystem(enumerate, SUBSYSTEM_FILTER);
    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);

    udev_list_entry_foreach(dev_list_entry, devices)
    {
        struct udev_device *dev;
        const char* dev_path = udev_list_entry_get_name(dev_list_entry);
        dev = udev_device_new_from_syspath(device, dev_path);

        if( isDeviceSD(dev) && isDeviceAdded(dev) )
        {
            retVal = true;
            udev_device_unref(dev);
            break;
        }

        udev_device_unref(dev);
    }
    udev_enumerate_unref(enumerate);

    return retVal;
}


static void print_device(struct udev_device *device, const char *source)
{
      struct timeval tv;
      struct timezone tz;

      gettimeofday(&tv, &tz);
      printf("%-6s[%llu.%06u] %-8s %s (%s)\n",
             source,
             (unsigned long long) tv.tv_sec, (unsigned int) tv.tv_usec,
             udev_device_get_action(device),
             udev_device_get_devpath(device),
             udev_device_get_subsystem(device));

            struct udev_list_entry *list_entry;

            udev_list_entry_foreach(list_entry, udev_device_get_properties_list_entry(device))
                  printf("%s=%s\n",
                         udev_list_entry_get_name(list_entry),
                         udev_list_entry_get_value(list_entry));
            printf("\n");

}
