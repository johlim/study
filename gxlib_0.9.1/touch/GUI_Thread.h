#ifndef __GUI_THREAD_H__
#define __GUI_THREAD_H__

#pragma pack(1)
///////////////////////////////////////////////////////////////////////
// define
///////////////////////////////////////////////////////////////////////
typedef struct _THREAD_STATUS
{
    pthread_t p_thread;
    int id;
    int argument;
    int ret;
    int running;
} GUI_THREAD_t;


///////////////////////////////////////////////////////////////////////
// external variable
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
// external function
///////////////////////////////////////////////////////////////////////


#if 0
/* example
static GUI_THREAD_t thrTouch;

static void *GUI_Thread_Touch(void *arg)
{

    while( thrTouch.running == 1 )
    {

    }

    return (void *)1;
}

int GUI_ThreadTouch_Start(int arg)
{
    thrTouch.argument = arg;
    thrTouch.running = 1;

    thrTouch.id = pthread_create(&thrTouch.p_thread, NULL, GUI_Thread_Touch, (void *)&thrTouch.argument);
    if (thrTouch.id < 0)
    {
        perror("Thread Touch");
        return -1;
    }
    // Create thread
    printf("** Thread Touch Start arg[%d]\n", thrTouch.argument);

    return 1;
}

int GUI_ThreadTouch_End(void)
{
    int ret;

    thrTouch.running = 0;
    pthread_join(thrTouch.p_thread, (void **)&ret);   // Wait untill thread is end
    printf("** Thread Touch End ret[%d]\n", thrTouch.ret);

    return ret;
}
*/
#endif

#endif