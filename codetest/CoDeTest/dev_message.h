
#ifndef __MP_MESSAGE_HEADER__
#define __MP_MESSAGE_HEADER__

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
	Dev_ERROR_SIGNAL = 0xF0000001
} MPMsgID;

typedef struct
{
	guint		msgid;
	gpointer	pdata;
	guint		datasize;
} DevMsgNode;

typedef struct
{
	GAsyncQueue*	hAsync;
	GQueue			*hFreeQueue;
	GQueue			*hPendQueue;
	DevMsgNode		*pNode;
	gpointer		pData;
	guint			maxmsg;
	guint			maxmsgsize;
} DevMsgStruct;

typedef void* DevMsgHandle;

DevMsgHandle DevMessageCreate(gint maxmsg, gint maxmsgsize);
gboolean DevMessageSend(DevMsgHandle hMsg, DevMsgNode *data);
gboolean DevMessageReceive(DevMsgHandle hMsg, DevMsgNode *data, gint timeout); // timeout ms
void DevMessageDestroy(DevMsgHandle hMsg);

#ifdef __cplusplus
}
#endif

#endif
