#include <stdint.h>

#define UINT32 uint32_t

typedef struct __attribute__((__packed__)) {
    UINT32 Year;
    UINT32 Month;
    UINT32 Day;
    UINT32 WeekDay;
    UINT32 Hour;
    UINT32 Minute;
    UINT32 Second;
} AMBA_RTC_DATE_TIME_s;

typedef struct __attribute__((__packed__)) _AIM_SCAN_HEADER_s {
    char                        code[4];
    UINT32                      version;
    unsigned char               reserved[20];
} AIM_SCAN_HEADER_s;

typedef struct __attribute__((__packed__)) _AIM_SCAN_RECORD_s {
    char                        filename[256];
    UINT32                      filesize;
    UINT32                      allocatesize;
    UINT32                      isdir;
    AMBA_RTC_DATE_TIME_s        modifiedtime;

    UINT32                      param1;
    UINT32                      param2;
    UINT32                      param3;
    UINT32                      param4;
    UINT32                      param5;
} AIM_SCAN_RECORD_s;
