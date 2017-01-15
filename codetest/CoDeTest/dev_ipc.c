/**
 * Copyright (c) 2007-2013 Core Logic, Inc. All Rights Reserved.
 *
 * THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 * BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 * CORE LOGIC, INC.
 *
 *
 *
*/
#include <glib.h>
#include <string.h>
#include <mqueue.h>
#include "clbbipcapi.h"
#include "dev_message.h"
#include "dev_ipc.h"

static DevMsgHandle g_hIPCMsg = NULL;
static GThread *pIPCThread = NULL;
static gboolean g_bIPCTaskRun = TRUE;
static BBIpcHandle g_hIPC_recv = NULL;
static BBIpcHandle g_hIPC_send = NULL;

extern int g_bQuit;
void cleanup_local_resource(void)
{
	g_print ("cleanup_local_resource\n");

    if (g_hIPC_recv)
    CLBBIpcDestroy(g_hIPC_recv);
    g_hIPC_recv = NULL;

    if (g_hIPC_send)
    CLBBIpcDestroy(g_hIPC_send);
	g_hIPC_send = NULL;

    g_bQuit = 1; //QUIT 설정
}

static void DevIPCTask(void)
{
	BBIpcMsg ipcmsg;
//		DevMsgNode msg;
	gboolean ret = FALSE;
	g_print ("DevIPCTask Started\n");

	while(g_bIPCTaskRun)
	{
		memset(&ipcmsg, 0, sizeof(BBIpcMsg));
		ret = CLBBIpcRecv(g_hIPC_recv, &ipcmsg, 100);
		if(ret)
		{
			g_print ("DevIPCTask CLBBIpcRecv success (%d)\n", ipcmsg.msgtype);
//				memset(&msg, 0, sizeof(DevMsgNode));
			switch(ipcmsg.msgtype)
			{
//				case CLMP_START:
//					g_print ("DevIPCTask received MP START message\n");
//					msg.msgid = PLAYER_PLAY;
//					msg.pdata = ipcmsg.pdata;	// file path for playing
//					msg.datasize = ipcmsg.datasize;
//					DevMessageSend(g_hIPCMsg, &msg);
//					break;
//				case CLMP_STOP:
//					g_print ("DevIPCTask received MP STOP message\n");
//					msg.msgid = PLAYER_STOP;
//					DevMessageSend(g_hIPCMsg, &msg);
//					break;
//				case CLMP_PAUSE:
//					g_print ("DevIPCTask received MP PAUSE message\n");
//					msg.msgid = PLAYER_PAUSE;
//					DevMessageSend(g_hIPCMsg, &msg);
//					break;
//				case CLMP_RESUME:
//					g_print ("DevIPCTask received MP RESUME message\n");
//					msg.msgid = PLAYER_RESUME;
//					DevMessageSend(g_hIPCMsg, &msg);
//					break;
//				case CLMP_SEEK:
//					g_print ("DevIPCTask received MP SEEK message\n");
//					{
//						unsigned int msec = 1000*10;
//						msg.msgid = PLAYER_SEEK;
//						msg.pdata = &msec;
//						msg.datasize = sizeof(msec);
//						DevMessageSend(g_hIPCMsg, &msg);
//					}
//					break;
//				case CLMP_FW:
//					g_print ("DevIPCTask received MP FW message\n");
//					{
//						unsigned int msec = 1000;
//						msg.msgid = PLAYER_FORWARD;
//						msg.pdata = &msec;
//						msg.datasize = sizeof(msec);
//						DevMessageSend(g_hIPCMsg, &msg);
//					}
//					break;
//				case CLMP_BW:
//					g_print ("DevIPCTask received MP BW message\n");
//					msg.msgid = PLAYER_BACKWARD;
//					DevMessageSend(g_hIPCMsg, &msg);
//					break;
//				case CLMP_REQUEST_LEN:
//					g_print ("DevIPCTask received MP REQUEST LEN message\n");
//					msg.msgid = PLAYER_REQUEST_LEN;
//					DevMessageSend(g_hIPCMsg, &msg);
//					break;
//				case CLMP_REQUEST_POS:
//					g_print ("DevIPCTask received MP REQUEST POS message\n");
//					msg.msgid = PLAYER_REQUEST_POS;
//					DevMessageSend(g_hIPCMsg, &msg);
//					break;
//				case CLMP_EXIT:
//					g_print ("DevIPCTask received MP EXIT message\n");
//					msg.msgid = PLAYER_EXIT;
//					DevMessageSend(g_hIPCMsg, &msg);
//					break;
			default:
				g_print ("DVRIPCTask received unknown message(%d)\n", ipcmsg.msgtype);
				break;
			}
		}
	}

	CLBBIpcDestroy(g_hIPC_recv);
	CLBBIpcDestroy(g_hIPC_send);
	g_hIPC_recv = NULL;
	g_hIPC_send = NULL;
	pIPCThread = NULL;
	g_hIPCMsg = NULL;
	g_print ("DevIPCTask Exit\n");
	g_thread_exit(g_thread_self());
}

gboolean DevIPCStart(DevMsgHandle hMsg, int ipcKey)
{
    struct sigaction act;

    /* CTRL+C 시 resource 반환후 종료할 수 있도록 */
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGINT);
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags = 0;
    act.sa_handler =  cleanup_local_resource;
    if (sigaction(SIGINT, &act, NULL) < 0) {
        perror("sigaction");
        exit(1);
        }
    /* CTRL+C 시 resource 반환후 종료할 수 있도록 */

	g_print("DevIPCStart\n");

//    atexit(cleanup_local_resource);
//		g_hIPCMsg = hMsg;

//		if(!g_hIPC_recv) {
//			g_hIPC_recv = CLBBIpcCreate(MPCTRLMSGKEY);
//			if(!g_hIPC_recv) {
//				g_print("DevIPCStart CLBBIpcCreate (recv mq) failed\n");
//				return FALSE;
//			}
//		}
#if 0
	if(!g_hIPC_send) {
		g_hIPC_send = CLBBIpcCreate(BLACKBOXMSGKEY);// MPSTATMSGKEY  or BLACKBOXMSGKEY
		if(!g_hIPC_send) {
			g_print("DevIPCStart CLBBIpcCreate (send mq BLACKBOXMSGKEY) failed\n");
			return FALSE;
		}
	}
#endif

#if 0
	if(!g_hIPC_send) {
		g_hIPC_send = CLBBIpcCreate(MPCTRLMSGKEY);// MPSTATMSGKEY  or BLACKBOXMSGKEY
		if(!g_hIPC_send) {
			g_print("DevIPCStart CLBBIpcCreate (send mq MPCTRLMSGKEY) failed\n");
			return FALSE;
		}
	}
#endif

#if 1
	if(!g_hIPC_send) {
		g_hIPC_send = CLBBIpcCreate(ipcKey);// MPSTATMSGKEY  or BLACKBOXMSGKEY
		if(!g_hIPC_send) {
			g_print("DevIPCStart CLBBIpcCreate (send mq MPSTATMSGKEY %08x) failed\n", ipcKey);
			return FALSE;
		}
	}
#endif
//		if(!pIPCThread)
//		{
//			g_bIPCTaskRun = TRUE;
//			pIPCThread = g_thread_create_full((GThreadFunc)(DevIPCTask), NULL, 0x2000, FALSE, FALSE, G_THREAD_PRIORITY_LOW, 0);
//			if(!pIPCThread)
//			{
//				CLBBIpcDestroy(g_hIPC_recv);
//				g_hIPC_recv = NULL;
//				CLBBIpcDestroy(g_hIPC_send);
//				g_hIPC_send = NULL;
//				return FALSE;
//			}
//		}

	return TRUE;
}

void DevIPCDestroy()
{
	g_print("DevIPCDestroy\n");
	g_bIPCTaskRun = FALSE;
}

gboolean DevIPCSend(BBIpcMsg *msg)
{
	if(!CLBBIpcSend(g_hIPC_send, msg, FALSE)) {
		g_print("DevIPCSend failed!!\n");
		return FALSE;
	}
	return TRUE;
}

//	/**
//	 * MPIPC_GstEvtCB is Called by mpgst lib
//	 * and passes the event to mp main loop
//	 */
//	void MPIPC_GstEvtCB(int event, void *data, int data_size)
//	{
//		DevMsgNode msg;
//		g_print("MPIPC_GstEvtCB (0x%X)\n", event);
//		switch(event)
//		{
//			case CLMP_STATE_START:
//				msg.msgid = (guint)PLAYER_STAT_START;
//				break;
//			case CLMP_STATE_STOP:
//				msg.msgid = (guint)PLAYER_STAT_STOP;
//				break;
//			case CLMP_STATE_EOS:
//				msg.msgid = (guint)PLAYER_STAT_EOS;
//				break;
//		}
//		msg.pdata = (gpointer)data;
//		msg.datasize = (guint)data_size;
//		DevMessageSend(g_hIPCMsg, &msg);
//	}

/**
 * DevIPC_SendtoUI send Device event to clui
 */
void DevIPC_SendtoUI(int event, void *data, int data_size)
{
	BBIpcMsg ipcmsg = {0};

	g_print("DevIPC_SendtoUI (0x%X)\n", event);
	if(data_size > sizeof(ipcmsg.pdata)) {
		g_print("%s() warning! - param size (%d) is over than (%d)\n", __func__,
												data_size, sizeof(ipcmsg.pdata));
		data_size = sizeof(ipcmsg.pdata);
	}

	if(data && data_size) {
		memcpy(ipcmsg.pdata, data, data_size);
		ipcmsg.datasize = data_size;
	}

	ipcmsg.msgtype = (long)event;
	DevIPCSend(&ipcmsg); // send msg to ui
}

/**
 * DevIPC_SendtoDVR send Device event to cldvr
 */
void DevIPC_SendtoDVR(int event , void *data, int data_size)
{
	BBIpcMsg ipcmsg = {0};

	g_print("DevIPC_SendtoDVR (0x%X)\n", event);
	if(data_size > sizeof(ipcmsg.pdata)) {
		g_print("%s() warning! - param size (%d) is over than (%d)\n", __func__,
												data_size, sizeof(ipcmsg.pdata));
		data_size = sizeof(ipcmsg.pdata);
	}

	if(data && data_size) {
		memcpy(ipcmsg.pdata, data, data_size);
		ipcmsg.datasize = data_size;
	}

    ipcmsg.msgtype = (long)event;

	DevIPCSend(&ipcmsg); // send msg to ui
}
