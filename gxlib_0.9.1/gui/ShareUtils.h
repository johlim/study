#ifndef	_H_SHAREUTILS_H
#define _H_SHAREUTILS_H
/**
 * Copyright (c) 2007-2015 PLK, Inc. All Rights Reserved.
 *
 * THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 * BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 * PLK, INC.
 * @file ShareUtils.h
 * @brief Common utils func module \n
 * @author Jonghoan Lim (jhlim@plk.co.kr)
 */

/* Define  --------------------------------------------------------------*/
#if defined(__cplusplus)
extern "C" {
#endif
typedef enum {
	LEVEL_NONE = 0x0,
	LEVEL_ERROR = 0x1,
	LEVEL_DEBUG = 0x2,
	LEVEL_TRACE = 0x3
} BL_DBG_LEVEL;

typedef enum {
	MODULE_NONE		= 0x0,
	MODULE_UI 		= 0x1,
	MODULE_SYSTEM = 0x2,
	MODULE_RECORD = 0x4,
	MODULE_PLAY   = 0x8,
	MODULE_ADAS   = 0x16,
	MODULE_MCU    = 0x32,
	MODULE_ALL		= 0xFFFF
} BL_DBG_MODULE;

typedef struct _shmeminfo {
	int infocount;
	unsigned char * info[8];
} shmeminfo;

/*
 * * Message Data Structure
 * */
#define  OPX_MSG_SIZE   (256-16) // 20161006 chnage 240byte(internal reserve 4byte)

typedef struct _OPX_MESSAGE
{
	long		msg_type;		// message type
	int		msg_id;			// message id
	long		size;			// contents size
	unsigned char contents[OPX_MSG_SIZE];		// user contents
} OPX_MESSAGE;

#define MSG_WAIT	(0)
#define MSG_NOWAIT	(1)
#ifndef TRUE
	#define TRUE                (1)
#endif
#ifndef FALSE
	#define FALSE               (0)
#endif

typedef void* dvrMsgHandle; // PORTING
/* Define variable  -----------------------------------------------------*/
enum __MSG_TYPE_ADAS__
{
	MSG_TYPE_ADAS	= 100,		// must be the first one
	MSG_TYPE_MCU_COMMAND	= 200, // micom app <-> carblx
};

enum __MSG_ID_ADAS__
{
	MSG_ADAS_TOTAL_INFO     = MSG_TYPE_ADAS,
	MSG_ADAS_MAIN_INFO,
	/* temporary */
	MSG_TEST_TOUCH_EVENT,
	MSG_TEST_KEY_EVENT,
	MSG_TEST_GSENSOR_EVENT,
	MSG_TEST_ETC_EVENT,
    /* ADAS DEBUG */
	MSG_ADAS_DRAW_LINE,
	MSG_ADAS_DRAW_NUMBER,
	MSG_ADAS_DBG_INFO
};
enum __MSG_ID_MCU__
{
    MSG_POWER_STATE_OFF        = MSG_TYPE_MCU_COMMAND,
    MSG_POWER_STATE_ON,
    MSG_POWER_STATE_REBOOT,
    MSG_POWER_STATE_SUSPEND,
    MSG_POWER_STATE_PARKING,
    MSG_POWER_STATE_MCU_RESET,
};
/* Define extern variable & function  -----------------------------------*/
#define CLTRACE(M...)	{\
			BL_Trace(__FILE__,__LINE__,__func__,M);}


/* Function prototype  --------------------------------------------------*/
void bind_process_to_core(unsigned int cpumask);
void bind_pthread_to_core(unsigned int cpumask);

//  module arg can not support yet. must be set NULL
void BL_Trace(const char* file, int line, const char* func, const int module, BL_DBG_LEVEL level, const char* format, ...);
void SET_TraceModule(BL_DBG_MODULE module);
void SET_TraceLevel(BL_DBG_LEVEL level );

//  module sharemem
int ui_bb_shm_start(void);
void ui_bb_shm_stop(void);
int ui_bb_shm_attach(shmeminfo * output);
void ui_bb_shm_detach(shmeminfo * input);

//  module ShareMsg
int	ShareMsgQueueOpen( void );
int	ShareMsgQueueClose( void );
int	ShareMsgQueueRcv( OPX_MESSAGE *msg, int type, int flag );
int	ShareMsgQueueRemove( void );
int	ShareMsgQueueReset( int msgType );
int	ShareMsgQueueSend( OPX_MESSAGE *msg );

//  module McuMsg
int	McuMsgQueueOpen( void );
int	McuMsgQueueClose( void );
int	McuMsgQueueRcv( OPX_MESSAGE *msg, int type, int flag );
int	McuMsgQueueRemove( void );
int	McuMsgQueueReset( int msgType );
int	McuMsgQueueSend( OPX_MESSAGE *msg );

// module ShareTime

unsigned long long DVRGetmsTime();


#if defined(__cplusplus)
};
#endif
#endif

