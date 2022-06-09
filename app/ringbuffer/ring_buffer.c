#include "ring_buffer.h"

/** ----------------------------------------------------------------------------
@brief  링버퍼에 데이터 저장
@remark 저장할 데이터는 최대 MAX_RING_DATA_SIZE로 저장 
@param  ring : 링버퍼 포인터
@param  data : 저장할 데이터
@param  sz_data : 데이터 길이
@return -
 -----------------------------------------------------------------------------*/
void ring_put( ring_t *ring, char *data, int sz_data){
  time_t curtime;
  time(&curtime);
  // 링버퍼의 개별 저장소보다 데이터가 크다면
  if ( MAX_RING_DATA_SIZE < sz_data)    sz_data = MAX_RING_DATA_SIZE; 

  // ring에 데이터 저장
  ring->item[ring->tag_head].sz_data = sz_data;
  memcpy( ring->item[ring->tag_head].data, data, sz_data);
  ring->item[ring->tag_head].updatetime = curtime;
  // ring tag 조정
  ring->tag_head = ( ring->tag_head +1) % MAX_RING_SIZE; // head 증가
  if ( ring->tag_head == ring->tag_tail){ // 버퍼가 모두 찼다면
    ring->tag_tail = ( ring->tag_tail +1) % MAX_RING_SIZE; // tail 증가
  }
}

/** ----------------------------------------------------------------------------
@brief  링버퍼 내의 데이터 요청
@remark 수신 버퍼는 0으로 초기화 
@remark 수신 버퍼에는 최대 sz_buff만큼 저장 
@param  ring : 링버퍼 포인터
@param  buff : 데이터 수신 버퍼
@param  sz_buff : 버퍼 크기
@return 데이터 길이
 -----------------------------------------------------------------------------*/
int ring_get( ring_t *ring, char *buff, int sz_buff){

  // 큐에 데이터가 없다면 복귀
  if ( ring->tag_head == ring->tag_tail){
    return 0; // 테이터 없음
  }

  // 큐 데이터 구하기
  memset( buff, 0, sz_buff);
  int sz_data = ring->item[ring->tag_tail].sz_data;
  if ( sz_buff < sz_data)   sz_data= sz_buff;             // 수신 버퍼 크기만큼 복사
  memcpy( buff, ring->item[ring->tag_tail].data, sz_data);

  ring->tag_tail = ( ring->tag_tail +1) % MAX_RING_SIZE;  // tail 증가

  return sz_data;
}

/** ----------------------------------------------------------------------------
@brief  링버퍼에 데이터가 있는지의 여부
@remark -
@param  ring : 링버퍼 포인터
@return TRUE == 데이터 있음
 -----------------------------------------------------------------------------*/
int ring_exists( ring_t *ring){

  return ring->tag_head != ring->tag_tail; // head 와 tail 값이 다르다면 데이터 있음
}

/** ----------------------------------------------------------------------------
@brief 링버퍼 초기화
@remark -
@param ring : 링버퍼 포인터
 -----------------------------------------------------------------------------*/
void ring_init( ring_t *ring){

  ring->tag_head = ring->tag_tail = 0; // 태그 값을 0으로 초기화
}

int ring_diff( ring_t *ring){

  // 큐에 데이터가 없다면 복귀
  if ( ring->tag_head == ring->tag_tail){
    return 0; // 테이터 없음
  }

  
  // 큐 확인
 int diff = (int)difftime(ring->item[ring->tag_head-1].updatetime,ring->item[ring->tag_tail].updatetime);
  printf("tail (%d) %s diff(%d)\n", ring->tag_tail, ring->item[ring->tag_tail].data, diff);
  printf("head- 1 (%d) %s\n", ring->tag_head-1, ring->item[ring->tag_head-1].data );
  if ( ring->tag_head -1 < 0)
  printf("head (%d) %s\n", MAX_RING_SIZE-1, ring->item[MAX_RING_SIZE-1].data );
    
  return 1;
}
