#include <stdio.h>
typedef	unsigned char		BYTE;
typedef	signed char			SBYTE;
typedef	unsigned short		WORD;
typedef	signed short		SWORD;
typedef	unsigned long		DWORD;
typedef	signed long			SDWORD;
typedef	unsigned long long	QWORD;
typedef	long long			SQWORD;
typedef	unsigned char		BOOL;
typedef void				VOID;
typedef	float				FLOAT;
typedef double				DOUBLE;

#ifdef __USE_LARGEFILE
typedef QWORD				SIZE_T;
typedef SQWORD				OFF_T;
#else
typedef DWORD				SIZE_T;
typedef SDWORD				OFF_T;
#endif

typedef void *				NC_LIST;
typedef void *				NC_TIMER;

#define STRUCT_PACK//			__attribute__ ((packed))
typedef struct tagMotionSense
{
	BYTE	nSensitivity;
	BYTE	nSpatial;
	BYTE	nBlackLevel;
	BYTE	nWhiteLevel;
} STRUCT_PACK KSense, *PKSense;

typedef struct tagMotion
{
	BOOL   bEnable;
	KSense   Sensitivity;
	DWORD   Area[36][2];      //   45 * 36 (NTSC = PAL)
	DWORD   nMaskCount;         //  motion masking count
	BYTE   nPostEventRecTime;   //   0(DISABLE), 1 ~ 60
	BYTE   nBuzzerTime;      //   0 ~ 59, 0xFF(Always), 0xFE(Disable)
	BYTE   nAlarmTime;         //   0 ~ 59, 0xFF(Alaways), 0xFE(Disable)   
	BOOL   bMotionTrace;
} STRUCT_PACK KMotion, *PKMotion;


int main(void)
{

	printf("%d size of KMotion \n", sizeof(KMotion));

	return 0;
}
