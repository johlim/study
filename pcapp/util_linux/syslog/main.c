#include <syslog.h>
int main(int argc, char * argv[])
{
	int i=0;

	openlog("launcher", LOG_PID , LOG_USER|LOG_DEBUG|LOG_CONS);
	syslog(LOG_USER|LOG_DEBUG|LOG_CONS,"restart %d", i);
	closelog();
}

/*
 * example 
 *
 */
#if 0
setlogmask (LOG_UPTO (LOG_NOTICE));

openlog ("exampleprog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

syslog (LOG_NOTICE, "Program started by User %d", getuid ());
#endif
