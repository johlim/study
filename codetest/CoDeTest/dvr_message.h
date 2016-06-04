
#ifndef __DVR_MESSAGE_HEADER__
#define __DVR_MESSAGE_HEADER__

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
	DVR_EVENT = 1,
	DVR_GSENSOR_DATA,
	DVR_GPS_DATA,
	DVR_OBD_DATA,
	DVR_INF_START,
	DVR_INF_STOP,
	DVR_PARK_START,
	DVR_PARK_STOP,
	DVR_START,
	DVR_STOP,
	DVR_STOP_DIRECT,
	DVR_EXIT,
	DVR_DISPLAY,
	DVR_PIP_SET,
	DVR_GPS_START,
	DVR_GSEN_START,
	DVR_EXTPROC_ENABLE,
	DVR_WRITE_DISABLE,
	DVR_CFG_UPDATE,
	DVR_PCM_PLAY,
	DVR_PCM_EXIT,
	DVR_FILEMAN_ERROR,
	DVR_GSENSOR_MOVEMENT_IN,
	DVR_GSENSOR_MOVEMENT_OUT,
	DVR_USER_REC_START,
	DVR_USER_REC_STOP,		
	DVR_STATE_RESERVED1,
	DVR_STATE_RESERVED2,
	DVR_STATE_RESERVED3,
	DVR_BUTTON_1_DOWN,
	DVR_BUTTON_1_UP,
	DVR_BUTTON_2_DOWN,
	DVR_BUTTON_2_UP,
	DVR_BUTTON_3_DOWN,
	DVR_BUTTON_3_UP,	
	DVR_BUTTON_1_LONG_DOWN,
	DVR_BUTTON_2_LONG_DOWN,
	DVR_BUTTON_3_LONG_DOWN,
	DVR_PCM_WARNING_SD_REMOVED,
	DVR_TVOUT_DETECTED,
	DVR_TVOUT_REMOVED,
	DVR_LDWS_ENABLE,
	DVR_LDWS_DISABLE,
	DVR_LDWS_WARNING_LEFT,
	DVR_LDWS_WARNING_RIGHT,
	DVR_ERROR_SIGNAL = 0xF0000001
}DVR_MSG_ID;

typedef struct
{
	guint		msgid;
	gpointer	pdata;
	guint		datasize;
}DVRMsgNode;

typedef struct
{
	GMutex			*hLock;
	GAsyncQueue		*hAsync;
	GQueue			*hFreeQueue;
	GQueue			*hPendQueue;
	DVRMsgNode		*pNode;
	gpointer		pData;
	guint			maxmsgcount;
	guint			maxmsgsize;
}dvrMsgStruct;

typedef void* dvrMsgHandle;

dvrMsgHandle DVRMessageCreate(gint maxmsgcount, gint maxmsgsize);
gboolean DVRMessageSend(dvrMsgHandle hMsg, DVRMsgNode *data);
gboolean DVRMessageReceive(dvrMsgHandle hMsg, DVRMsgNode *data, gint timeout); // timeout ms
void DVRMessageDestroy(dvrMsgHandle hMsg);

#ifdef __cplusplus
}
#endif

#endif
