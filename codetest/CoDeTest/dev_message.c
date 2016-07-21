
#include <glib.h>
#include <string.h>
#include <mqueue.h>

#include "dev_message.h"

DevMsgHandle DevMessageCreate(gint maxmsg, gint maxmsgsize)
{
	DevMsgStruct *msg = NULL;
	gpointer nodedata = NULL;
	gint i;

	msg = g_malloc0(sizeof(DevMsgStruct));
	if(!msg)
	{
		g_print("DVRMessageCreate malloc failed\n");
		return NULL;
	}

	msg->hAsync = g_async_queue_new();
	if(!msg->hAsync)
	{
		g_print("DVRMessageCreate async queue create failed\n");
		goto ERROR_RETURN;
	}

	msg->hFreeQueue = g_queue_new();
	if(!msg->hFreeQueue)
	{
		g_print("DVRMessageCreate free queue create failed\n");
		goto ERROR_RETURN;
	}

	msg->hPendQueue = g_queue_new();
	if(!msg->hPendQueue)
	{
		g_print("DVRMessageCreate pend queue create failed\n");
		goto ERROR_RETURN;
	}

	msg->pData = nodedata = g_malloc(maxmsg * maxmsgsize);
	if(!msg->pData)
	{
		g_print("DVRMessageCreate data malloc failed maxmsg(%d) maxsize(%d)\n", maxmsg, maxmsgsize);
		goto ERROR_RETURN;
	}

	msg->pNode = (DevMsgNode*)g_malloc0(sizeof(DevMsgNode) * maxmsg);
	if(!msg->pNode)
	{
		g_print("DevMessageCreate node malloc failed maxmsg(%d) nodesize(%d)\n", maxmsg, sizeof(DevMsgNode));
		goto ERROR_RETURN;
	}

	for(i = 0; i < maxmsg; i++)
	{
		msg->pNode[i].pdata = nodedata;
		g_queue_push_tail(msg->hFreeQueue, &msg->pNode[i]);
		nodedata += maxmsgsize;
	}

	msg->maxmsg = maxmsg;
	msg->maxmsgsize = maxmsgsize;

	return (DevMsgHandle)msg;

ERROR_RETURN:

	if(msg->pData)
		g_free(msg->pData);
	if(msg->pNode)
		g_free(msg->pNode);
	if(msg->hPendQueue)
		g_queue_free(msg->hPendQueue);
	if(msg->hFreeQueue)
		g_queue_free(msg->hFreeQueue);
	if(msg->hAsync)
		g_async_queue_unref(msg->hAsync);
	g_free(msg);

	return NULL;
}

gboolean DevMessageSend(DevMsgHandle hMsg, DevMsgNode *data)
{
	DevMsgStruct *msg = (DevMsgStruct*)hMsg;
	DevMsgNode *freenode;

	if(!msg)
	{
		g_print("DVRMessageSend invalid msg handle\n");
		return FALSE;
	}

	if(!data)
	{
		g_print("DVRMessageSend invalid arguments data(0x%p)\n", data);
		return FALSE;
	}

	if(data->datasize > msg->maxmsgsize)
	{
		g_print("DVRMessageSend data size is too big max(%d) cur(%d)\n", msg->maxmsgsize, data->datasize);
		return FALSE;
	}

	freenode = (DevMsgNode*)g_queue_pop_head(msg->hFreeQueue);
	if(!freenode)
	{
		g_print("DVRMessageSend mag queue full\n");
		return FALSE;
	}

	freenode->msgid = data->msgid;
	if(data->datasize)
	{
		memcpy(freenode->pdata, data->pdata, data->datasize);
		freenode->datasize = data->datasize;
	}

	g_queue_push_tail(msg->hPendQueue, freenode);

	g_async_queue_push(msg->hAsync, (gpointer)freenode);

	return TRUE;
}

gboolean DevMessageReceive(DevMsgHandle hMsg, DevMsgNode *data, gint timeout)
{
	DevMsgStruct *dvrmsg = (DevMsgStruct*)hMsg;
	GTimeVal endtime;
	DevMsgNode *pData;
	DevMsgNode *pPend;
	gpointer val = 0;

	if(!dvrmsg)
	{
		g_print("DVRMessageReceive invalid msg handle\n");
		return FALSE;
	}

	if(!data)
	{
		g_print("DVRMessageReceive invalid arguments data(%p))\n", data);
		return FALSE;
	}

	if(timeout)
	{
		g_get_current_time(&endtime);
		g_time_val_add(&endtime, timeout*1000);
		val = g_async_queue_timed_pop(dvrmsg->hAsync, &endtime);
		if(val)
		{
			pData = (DevMsgNode*)val;
			pPend = (DevMsgNode*)g_queue_pop_head(dvrmsg->hPendQueue);
			//g_print("DVRMessageReceive pend queue pop node(0x%08x)\n", pPend);
			if(pData != pPend)
			{
				g_print("DVRMessageReceive timeout(%d) not matched async queue(%p) with queue(%p)\n", timeout, pData, pPend);
				return FALSE;
			}
			if(data->datasize < pPend->datasize)
			{
				g_print("DVRMessageReceive timeout(%d) invalid size(%d) datasize(%d)\n", timeout, data->datasize, pPend->datasize);
				return FALSE;
			}
			data->msgid = pPend->msgid;
			if(pPend->datasize)
			{
				memcpy(data->pdata, pPend->pdata, pPend->datasize);
				data->datasize = pPend->datasize;
			}
			//g_print("DVRMessageReceive free queue push node(0x%08x)\n", pPend);
			g_queue_push_tail(dvrmsg->hFreeQueue, pPend);
		}
		else
		{
			//g_print("DVRMessageReceive timeout or error\n");
			return FALSE;
		}
	}
	else
	{
		val = g_async_queue_pop(dvrmsg->hAsync);
		if(val)
		{
			pData = (DevMsgNode*)val;
			pPend = (DevMsgNode*)g_queue_pop_tail(dvrmsg->hPendQueue);
			if(pData != pPend)
			{
				g_print("DVRMessageReceive not matched async queue(%p) with queue(%p)\n", pData, pPend);
				return FALSE;
			}
			if(data->datasize < pPend->datasize)
			{
				g_print("DVRMessageReceive invalid size(%d) datasize(%d)\n", data->datasize, pPend->datasize);
				return FALSE;
			}
			data->msgid = pPend->msgid;
			if(pPend->datasize)
			{
				memcpy(data->pdata, pPend->pdata, pPend->datasize);
				data->datasize = pPend->datasize;
			}
		}
		else
		{
			return FALSE;
		}
	}

	return TRUE;
}

void DevMessageDestroy(DevMsgHandle hMsg)
{
	DevMsgStruct *dvrmsg = (DevMsgStruct*)hMsg;

	if(dvrmsg->pData)
		g_free(dvrmsg->pData);
	if(dvrmsg->pNode)
		g_free(dvrmsg->pNode);
	if(dvrmsg->hPendQueue)
		g_queue_free(dvrmsg->hPendQueue);
	if(dvrmsg->hFreeQueue)
		g_queue_free(dvrmsg->hFreeQueue);
	if(dvrmsg->hAsync)
		g_async_queue_unref(dvrmsg->hAsync);
	g_free(dvrmsg);
}
