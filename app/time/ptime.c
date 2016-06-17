#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/ioctl.h>
int main(void)
{
	time_t t;
	struct tm tm;
	char time_str[128];
	time(&t);

	localtime_r( &t, &tm );

	printf("\n LOCAL\t");
	sprintf( time_str, "%04d-%02d-%02d %02d:%02d:%02d",	\
			tm.tm_year+1900,
			tm.tm_mon+1,
			tm.tm_mday,
			tm.tm_hour,
			tm.tm_min,
			tm.tm_sec );
	printf("%s",time_str);

	printf("\n GM\t");

	gmtime_r(&t,&tm);	
	sprintf( time_str, "%04d-%02d-%02d %02d:%02d:%02d",	\
			tm.tm_year+1900,
			tm.tm_mon+1,
			tm.tm_mday,
			tm.tm_hour,
			tm.tm_min,
			tm.tm_sec );
	printf("%s",time_str);
	printf("\n");
	return 0;
}
