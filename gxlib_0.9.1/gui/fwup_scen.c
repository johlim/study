/**
 * Copyright (c) 2007-2017 PLK, Inc. All Rights Reserved.
 *
 * THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 * BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 * PLK, INC.
 *
 * @file fwup_scen.c
 * @brief gpio_ui_scen \n
 * @author developer (developers@plk.co.kr)
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#include <ShareUtils.h>

/* Define  --------------------------------------------------------------*/
#define DBGOUT	 printf
typedef struct userinput_ctx
{
	unsigned int current_scen;
	unsigned int prev_scen;
	unsigned int next_scen;
	unsigned int last_scen;
	unsigned int running;
	unsigned int start;
} Tuserinput_ctx;

typedef struct touch_msg
{
	int touchType;
	int touchX;
	int touchY;
	int width;
	int height;
} Ttouch_msg;

// msg type define
enum __MSG_TYPE_UI__
{
	MSG_TYPE_TOUCH		= 100,
	MSG_TYPE_KEY      = 200,
	MSG_TYPE_GSENSOR	= 300,
	MSG_TYPE_SUPERCAP	= 400,
	MSG_TYPE_GPIO   	= 500,
};

/* Define variable  -----------------------------------------------------*/
static key_t	s_msgQueueKey;
static Tuserinput_ctx u_ctx;
static pthread_t	s_tid_userinputmsg=0;
/* Define extern variable & function  -----------------------------------*/

/* Function prototype  --------------------------------------------------*/
int open_userinput_handler(int *Msg);
int close_userinput_handler(int *Msg);
void callback_userinput(int *touchMsg);
/* Function implementation  ---------------------------------------------*/

/**
 *  \brief Queue Create or attach
 *
 *  \return TRUE, FALSE;
 *
 */
static int UIMsgQueueCreate( void )
{
	s_msgQueueKey = msgget( (key_t)0x6638, IPC_CREAT|IPC_EXCL| 0666 );

	if (s_msgQueueKey == -1)
	{
		s_msgQueueKey = msgget( (key_t)0x6638, 0666 );

		if (s_msgQueueKey == -1)
		{
			perror("msgget() attach ");
		}

		return FALSE;
	}
	return TRUE;
}

/**
 *  \brief Brief
 *
 *  \return msgsnd return
 *
 *  \details Details
 */
static int UIMsgQueueRemove( void )
{
	/* remove queue */
	return msgctl(s_msgQueueKey, IPC_RMID, 0);
}

/**
 *  \brief Brief
 *
 *  \param [in] msg  send to msg (pointer)
 *  \return msgsnd return
 *
 *  \details Details
 */
static int UIMsgQueueSend( OPX_MESSAGE *msg )
{
	return msgsnd( s_msgQueueKey, (void *)msg, sizeof(OPX_MESSAGE)-sizeof(long), IPC_NOWAIT);
}

/*
   menu struction
   intro->	fwup (left,down)

   ok -> fwup
   */
char menu_scen[2][2]={\
	{0,0},\
	{0,1}};

/**
 *  \brief Brief
 *
 *  \param [in] arg not used
 *  \return return 0
 *
 *  \details msg handler with while loop
 */
static void * ThreadProcCheckUserInputMsg( void* arg )
{
	OPX_MESSAGE rsv_msg;
	int type=MSG_TYPE_TOUCH, flag=IPC_NOWAIT;
	int ret, msgid;
	Ttouch_msg * pcontents;
	int x=0,y=0;
	/* clean message queue */
	while(msgrcv( s_msgQueueKey, &rsv_msg, sizeof(OPX_MESSAGE)-sizeof(long), type, flag) > 0);

	flag=0;//wait
	while(u_ctx.start)
	{
		// receive touch or key input
		ret = msgrcv( s_msgQueueKey, &rsv_msg, sizeof(OPX_MESSAGE)-sizeof(long), type, flag);

		if( u_ctx.running )
		{
			pcontents = (Ttouch_msg *)&(rsv_msg.contents);
			printf("i got message %x  %d %d %d \n",rsv_msg.contents, pcontents->touchType, pcontents->touchX, pcontents->touchY);

			if (pcontents->touchType==4) //left
			{
				printf("scen left\n");
				x++;
				if (x > 1) x= 1;
			}
			else if (pcontents->touchType==5) //right
			{
				printf("scen right\n");
				x--;
				if (x < 0) x= 0;
			}
			else if (pcontents->touchType==6) //up
			{
				y--;
				printf("scen up\n");
				if (y < 0) y= 0;
			}
			else if (pcontents->touchType==7) //down
			{
				y++;
				printf("scen down\n");
				if (y > 1) y= 1;
			}


			printf("current menu %d %d  \n",x,y);

			if (menu_scen[x][y] == 1)
			{
				printf("OK Staring fwup_start \n"); // call fwup_start
				//fwup_start(0,0);
			}
			// draw or call scen handle

		}
		//usleep(100*1000);
	}

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief Brief
 *
 *  \param [in] Msg not used
 *  \return success 0
 *
 *  \details Details
 */
int open_userinput_handler(int *Msg)
{
	int ret;

	ret = UIMsgQueueCreate();

	if (ret != TRUE)
	{
		// TODO do error handle
		DBGOUT("%s %d\n", __func__, __LINE__);
	}

	u_ctx.running=0;
	
	if (s_tid_userinputmsg == 0)
	{
		u_ctx.start =1;
		ret = pthread_create(  &s_tid_userinputmsg, NULL, ThreadProcCheckUserInputMsg, (void*)NULL );
		if (ret != 0)
			perror("pthread_create fail");
	}

	return ret;
}

/**
 *  \brief Brief
 *
 *  \param [in] Msg not used
 *  \return always 0
 *
 *  \details Details
 */
int close_userinput_handler(int *Msg)
{
	int ret=0;

	//if (s_tid_userinputmsg != 0)
	{
		u_ctx.start =0;
		u_ctx.running=0;
	}

	UIMsgQueueRemove();

	return ret;
}

/**
 *  \brief Brief
 *
 *  \param [in] touchMsg touch info
 *  \return NONE
 *
 *  \details Details
 */
void callback_userinput(int * touchMsg)
{
	OPX_MESSAGE snd_msg;
	Ttouch_msg	contents;
	int type=MSG_TYPE_TOUCH, id =0;// toggle
	int ret;

	DBGOUT("%s %d [%d] [%d] [%d] \n", __func__, __LINE__,touchMsg[0],touchMsg[1],touchMsg[2]);

	if (u_ctx.start==0)
	{
		DBGOUT("%s %d not ready \n", __func__, __LINE__);
		return;
	}
	/*
	   int touchType = touchMsg[0];
	   int touchX = touchMsg[1];
	   int touchY = touchMsg[2];
	   */
	snd_msg.msg_type=type;		// message type
	snd_msg.msg_id=id;			// message id
	snd_msg.size=12;			// byte
	contents.touchType = touchMsg[0];
	contents.touchX = touchMsg[1];
	contents.touchY = touchMsg[2];

	memcpy((void *)&snd_msg.contents, &contents, sizeof(Ttouch_msg));

	ret = UIMsgQueueSend(&snd_msg);
	if (ret)
	{
		DBGOUT("%s %d\n", __func__, __LINE__);
	}
}

void setRun_userinput(int value)
{
	u_ctx.running = value;
}
