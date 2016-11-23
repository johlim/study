#ifndef __CLBLACKBOXIPC_API__
#define __CLBLACKBOXIPC_API__

// message queue key (ipc)
#define BLACKBOXMSGKEY	0xA000 // cldvr
#define STREAMINGMSGKEY	0xA001
#define WEBCTRLMSGKEY	0xA002
#define UIMSGKEY		0xA003 // clui
#define PLAYERMSGKEY	0xA004 // clmp
#define USERMSGKEY1		0xA100 // reserved
#define USERMSGKEY2		0xA101 // reserved
#define USERMSGKEY3		0xA102 // reserved
#define USERMSGKEY4		0xA103 // reserved
#define USERMSGKEY5		0xA104 // reserved

// shared memory key (ipc)
#define FRAME_SHMEM_KEY	0xB000
#define USER_SHMEM_KEY	0xB001 // reserved
#define FRAME_SHMEM_SIZE	(2*1024*1024)

typedef void* BBIpcHandle;

#define BBIPCMSG_MAXSIZE	256

#define NCMEM_SHMEM_KEY 0xC000 // NCMEM Sharing KeyValue must be over '0xC000'
#define NCMEM_SHMEM_ALLOC_SIZE 2*1024*1024

typedef enum
{
	CLSHM_RW_ERROR = -1,
	CLSHM_RW_OK
} BBShmRet;

typedef struct _clbb_shm_struct
{
	unsigned int key;
	int id;
	void *addr;	// attached shared mem address
	int map_id;
} CLBBShmStruct;

typedef struct BBIpcMsg
{
	long msgtype;
	int datasize;
	char pdata[BBIPCMSG_MAXSIZE];
} BBIpcMsg;

typedef struct {
	unsigned int video_index;
	unsigned int x;
	unsigned int y;
	unsigned int w;
	unsigned int h;
} BBPIPSetParam;

typedef enum
{
	CLBB_START = 0x1001,
	CLBB_STOP = 0x1002,
	CLBB_UPDATE_CONF = 0x1003,
	CLBB_ALIVE = 0x1004,
	CLBB_PIP_SET = 0x1005,
	CLBB_EXIT = 0x1006,
	CLBB_PVREADY = 0x1007,

	CLBB_STATE_TVOUT_DETECTED = 0x1101,
	CLBB_STATE_TVOUT_REMOVED = 0x1102,
	CLBB_STATE_RESERVED3 = 0x1103,

	CLBB_MOUNT_OK = 0x1201,
	CLBB_MOUNT_FAIL = 0x1202,

	CLSS_START = 0x2001,
	CLSS_STOP = 0x2002,
	CLSS_SEND_DATA_FRONT = 0x2003,
	CLSS_SEND_DATA_REAR  = 0x2004,
	CLSS_MD_ENABLE = 0x2005,
	CLSS_MD_DISABLE = 0x2006,

	CLMP_START = 0x3001,
	CLMP_STOP = 0x3002,
	CLMP_PAUSE = 0x3003,
	CLMP_RESUME = 0x3004,
	CLMP_SEEK = 0x3005,
	CLMP_FW = 0x3006,
	CLMP_BW = 0x3007,
	CLMP_EXIT = 0x3008,
	CLMP_SET_MEDIA = 0x3101,
	CLMP_SET_DISP = 0x3102,

	CLMP_REQUEST_LEN = 0x4001,
	CLMP_REQUEST_POS = 0x4002,
	CLMP_REQUEST_FRAMEDATA = 0x4003,

	CLMP_STATE_START = 0x5001,
	CLMP_STATE_STOP = 0x5002,
	CLMP_STATE_EOS = 0x5003,
	CLMP_STATE_LEN = 0x5004,
	CLMP_STATE_POS = 0x5005,
	CLMP_STATE_VTRACKS = 0x5006,
	CLMP_STATE_FRAMEDATA_DONE = 0x5007,
	CLMP_STATE_FAIL = 0x5008,

	CLDEV_SD0_REMOVE = 0x7001,
	CLDEV_SD0_INSERT = 0x7002,
	CLDEV_OTG_REMOVE = 0x7003,
	CLDEV_OTG_INSERT = 0x7004,
	CLDEV_SD1_REMOVE = 0x7005,
	CLDEV_SD1_INSERT = 0x7006,

	CLDEV_SSM_MSG = 0x8001

} BBIpcMsgType;

// message queue api
BBIpcHandle CLBBIpcCreate(int msgkey);
void CLBBIpcDestroy(BBIpcHandle hIpc);
gboolean CLBBIpcSend(BBIpcHandle hIpc, BBIpcMsg *msg, gboolean bwait);
gboolean CLBBIpcRecv(BBIpcHandle hIpc, BBIpcMsg *msg, int mstimeout);	// timeout (ms)

// shared memory api
BBIpcHandle CLBBShmCreate(int shmkey, int size, void **out_ptr);
void CLBBShmDestroy(BBIpcHandle hShm);
int CLBBShmWrite(BBIpcHandle hShm, void * data, int size);
int CLBBShmRead(BBIpcHandle hShm, void **data, int size);

#endif
