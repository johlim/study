#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#define DLOG printf
void request_set_rtc(void)
{
	const char *value = "1625627755160";

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
		strncpy(str_epoch_ms, value, strlen(value));
		printf(" %s %lu \n", str_epoch_ms, strlen(value));
//epoch = strtol(value, &ptr, 10) / 1000;
		epoch = strtol(str_epoch_ms, &ptr, 10) / 1000;
	}

	DLOG("value = %s", value);
	DLOG("epoch = %ld", epoch);

	tm = gmtime(&epoch);

	year = tm->tm_year + 1900;
	month = tm->tm_mon + 1;
	mday = tm->tm_mday;
	hour = tm->tm_hour;
	min = tm->tm_min;
	sec = tm->tm_sec;

	DLOG("%s() year=%d, month=%d, day=%d, hour=%d, min=%d, sec=%d", __func__
			, year, month, mday, hour, min, sec);
}
