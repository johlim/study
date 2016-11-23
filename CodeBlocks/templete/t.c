#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define SYSLOG // OEM_SYS_Printf
#define APPLOG printf

//	#define NDEBUG
#ifndef NDEBUG
#define DEBUG(x) do {x;} while (0)		/* enable debugging        */
#define DEBUG_VAR(x) x					/* enable debugging decls  */
#else
#define DEBUG(x)						/* disable debugging       */
#define DEBUG_VAR(x)					/* disable debugging decls */
#endif

char buff[128];

static off_t calc_locate_filesize( struct stat * file_status )
{
	DEBUG(APPLOG("+(%d)", (unsigned int)file_status->st_size));
	DEBUG(APPLOG("+(%d)", (unsigned int)file_status->st_blocks));
	DEBUG(APPLOG("+(%d)", (unsigned int)file_status->st_blksize));
}
int main(int argc, char * argv[])
{
	int ret;
	int filesize=0;
	int len;
	char filename[128]={0,};
	struct stat file_status={0,};
    char * nullptr=0;
	if (argc < 2)
	return -1;

	len = strlen(argv[1]);

	strncpy(filename, argv[1], len);

	ret = stat(filename, &file_status);
	if (ret)
		printf("%s error %d", filename, len);
	filesize = calc_locate_filesize(&file_status);//file_status.st_size;

	return 0;
}
