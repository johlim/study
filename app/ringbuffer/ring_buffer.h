#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h> // ctime, difftime
#include <sys/types.h>
#include <sys/time.h> //gettimeofday
#include <sys/times.h> //times

#define MAX_RING_SIZE 6               // 링버퍼가 갖는 아이템 개수
#define MAX_RING_DATA_SIZE 20         // 링버퍼 내의 버퍼 개별 크기

typedef struct{                            // 링버퍼 안의 개별 버퍼        
  int sz_data;                            // 개별 버퍼에 복사된 실제 데이터 길이
  time_t updatetime;                        // 삽입시간
  char data[MAX_RING_DATA_SIZE];        // 개별 버퍼의 실제 저장 장소
} rign_item_t;    // 링버퍼 내 개별 저장소

typedef struct{
  int tag_head;                         // 쓰기 위치
  int tag_tail;                         // 읽기 위치
  rign_item_t item[MAX_RING_SIZE];        // 링버퍼 내의 저장 장소
} ring_t;        // 링버퍼

/** ----------------------------------------------------------------------------
@brief  링버퍼에 데이터 저장
@remark 저장할 데이터는 최대 MAX_RING_DATA_SIZE로 저장 
@param  ring : 링버퍼 포인터
@param  data : 저장할 데이터
@param  sz_data : 데이터 길이
@return -
 -----------------------------------------------------------------------------*/
void ring_put( ring_t *ring, char *data, int sz_data);

/** ----------------------------------------------------------------------------
@brief  링버퍼 내의 데이터 요청
@remark 수신 버퍼는 0으로 초기화 
@remark 수신 버퍼에는 최대 sz_buff만큼 저장 
@param  ring : 링버퍼 포인터
@param  buff : 데이터 수신 버퍼
@param  sz_buff : 버퍼 크기
@return 데이터 길이
 -----------------------------------------------------------------------------*/
int ring_get( ring_t *ring, char *buff, int sz_buff);
/** ----------------------------------------------------------------------------
@brief  링버퍼에 데이터가 있는지의 여부
@remark -
@param  ring : 링버퍼 포인터
@return TRUE == 데이터 있음
 -----------------------------------------------------------------------------*/
int ring_exists( ring_t *ring);
/** ----------------------------------------------------------------------------
@brief 링버퍼 초기화
@remark -
@param ring : 링버퍼 포인터
 -----------------------------------------------------------------------------*/
void ring_init( ring_t *ring);
int ring_diff( ring_t *ring);