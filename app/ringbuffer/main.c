#include "ring_buffer.h"

int main( void){
  char    *data1 = "manualkey";
  char    *data2 = "panickey";
  char    *data3 = "longmanualkey";
  ring_t   ring;

  ring_init( &ring);

  ring_put( &ring, data1, strlen( data1)); sleep(1);
  ring_put( &ring, data2, strlen( data2)); sleep(1);
  ring_put( &ring, data1, strlen( data1)); sleep(1);
  ring_put( &ring, data2, strlen( data2)); sleep(1);
  ring_put( &ring, data3, strlen( data3)); 

  printf( "두 번째 출력------------------------\n");
  while( 1){
    if ( ring_exists( &ring)){
      char buff[MAX_RING_DATA_SIZE];
      ring_diff(&ring);
      int  sz_data = ring_get( &ring, buff, sizeof( buff));      
      printf( "data size=%2d data string=%s\n", sz_data, buff);

    } 
    else {
      break;
    }
  }
}