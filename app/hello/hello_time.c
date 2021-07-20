#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#define DLOG printf
void request_set_rtc(void)
{
//	//const char *value = "1625627755160";
//	const char *value = "1626425073275";
        //const char *value = "1626426413605";
	const char *value = "1626678230449";
	//const char *value = "1626678220921";
	time_t epoch; 
	struct tm *tm;

	int year = 0;
	int month = 0;
	int mday = 0;
	int hour = 0;
	int min = 0;
	int sec = 0;

	{
		char *ptr = NULL;
		char str_epoch_ms[64]={0};
		long long int epoch_ms;
		time_t _epoch_sec;

		strncpy(str_epoch_ms, value, strlen(value));
		printf(" %s %lu \n", str_epoch_ms, strlen(value));
		_epoch_sec = epoch_ms = strtoll(str_epoch_ms, &ptr, 10);
		if (epoch_ms > 1000000000000LL)
		{
		   DLOG("1. epoch_ms = %lld is over \n", epoch_ms);
		   epoch_ms = (epoch_ms / 1000LL); 
		   DLOG("2. _epoch_sec = %ld \n", _epoch_sec);
		   _epoch_sec = (long)epoch_ms;
		   DLOG("3. _epoch_sec = %ld \n", _epoch_sec);
		}
		epoch = _epoch_sec;
	DLOG("value = %s\n", value);
	DLOG("epoch_ms = %lld\n", epoch_ms);
	DLOG("epoch = %ld\n", epoch);
	}


	tm = gmtime(&epoch);

	year = tm->tm_year + 1900;
	month = tm->tm_mon + 1;
	mday = tm->tm_mday;
	hour = tm->tm_hour;
	min = tm->tm_min;
	sec = tm->tm_sec;

	DLOG("\n %s() year=%d, month=%d, day=%d, hour=%d, min=%d, sec=%d", __func__
			, year, month, mday, hour, min, sec);

	DLOG("\n %ld \n", time(NULL));
}
