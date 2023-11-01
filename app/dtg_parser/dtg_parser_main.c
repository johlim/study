// gcc main.c -lm
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h> 
#define TRUE 		1
#define FALSE		0

#define U08			unsigned char
#define UINT8		unsigned char
#define UINT32		uint32_t
#define UINT64		uint64_t
#define INT32		int32_t
#define UINT16		uint16_t
#define DOUBLE      double
#define FLOAT       float
#define aim_strlen 	strlen
#define aim_cmp 	strcmp

#define MY_MEMSET	memset
#define MY_MEMCPY 	memcpy
#define MY_STRCPY 	strcpy
#define MY_STRCAT 	strcat
#define MY_STRCMP 	aim_cmp
#define MY_STRNCMP 	strncmp

#define MY_STRLEN 	strlen

#define AmbaMisra_TouchUnused 

#define AIM_MAX_BUFFER_SIZE                             2048
#define AIM_MID_BUFFER_SIZE                             1024
#define AIM_MIN_BUFFER_SIZE                             128

#define SVC_NG	    1
#define SVC_OK	    0
#define OK	        0


//===================================================================================
// dummy warpring
//===================================================================================

#define AIM_MDTG_HEADER_CODE        "MDTG"

#define AIM_MDTG_TASK_MAX_TRIP_COUNT                    99
#define AIM_MDTG_TASK_MAX_VALUE_SIZE                    24
#define AIM_MDTG_TASK_MAX_VALUE_COUNT                   20


typedef struct {
    UINT32 Year;
    UINT32 Month;
    UINT32 Day;
    UINT32 WeekDay;
    UINT32 Hour;
    UINT32 Minute;
    UINT32 Second;
} AMBA_RTC_DATE_TIME_s;

typedef struct AIM_MDTG_HEADER_s_ {
    char                    code[4];															// "MDTG" 고정
    UINT32                  version;															// 현재는 버전 0으로 시작. 차후 파일 포멧 변경시 버전 변경될 수 있음
    UINT32                  record_unit_size;													// sizeof(AIM_MDTG_RECORD_s)의 크기
    UINT32                  base_odometer;														// 일일 시작시의 odometer
    UINT32                  trip_cnt;															// TRIP의 개수
    UINT32                  offset[AIM_MDTG_TASK_MAX_TRIP_COUNT];								// TRIP의 시작 위치
    UINT32                  reserved[12];

    UINT32                  slack_cnt;															// 문자열 개수
    UINT32                  slack_unit_size;													// 문자열 최대 사이즈 (=AIM_MDTG_TASK_MAX_VALUE_SIZE)
    char                    slack[AIM_MDTG_TASK_MAX_VALUE_COUNT][AIM_MDTG_TASK_MAX_VALUE_SIZE];	// 문자열 버퍼
} __attribute__ ((packed)) AIM_MDTG_HEADER_s;

typedef struct AIM_MDTG_RECORD_s_ {
    UINT32                  id;										// TRIP의 아이디

    UINT8                   approval_idx;							// approval의 인덱스(헤더의 문자열을 참조하는 번호)
    UINT8                   serial_idx;								// serial의 인덱스(헤더의 문자열을 참조하는 번호)
    UINT8                   vehicle_id_idx;							// vehicle의 인덱스(헤더의 문자열을 참조하는 번호)
    UINT8                   vehicle_type;							// vehicle 타입
    UINT8                   vehicle_plate_idx;						// vehicle_plate의 인덱스(헤더의 문자열을 참조하는 번호)
    UINT8                   provider_code_idx;						// provider_code의 인덱스(헤더의 문자열을 참조하는 번호)
    UINT8                   driver_code_idx;						// driver_code의 인덱스(헤더의 문자열을 참조하는 번호)
    UINT8                   reserved_1;

    UINT32                  odometerday;							// 일일 운행거리 즉, (odometer - base_odometer)
    UINT32                  odometer;								// 총 주행거리
    AMBA_RTC_DATE_TIME_s    date;									// 년월일시분초

    UINT16                  vss_tick;								// 1초단위 평균 차속
    UINT16                  rpm_tick;								// 1초단위 평균 RPM

    UINT8                   brake_pressure;							// 브레이크 여부
     UINT8                   dtc;
    UINT8                   reserved_2[2];

    UINT32                  latitude;								// 위도
    UINT32                  longtitude;								// 경도

    UINT16                  true_course;							// 방향
    UINT16                  reserved_3;

    float                   accelx;									// 가속 X
    float                   accely;									// 가속 Y
    float                   accelz;									// 미사용

    //UINT8                   reserved_4[20];
} __attribute__ ((packed)) AIM_MDTG_RECORD_s;

//===================================================================================
// NEW
//===================================================================================

int read_header(FILE* file_ptr, AIM_MDTG_HEADER_s* header)
{
    int err = SVC_NG;

    printf("read_header > \n");
    if((file_ptr!=NULL) && (header!=NULL)){
        int err1=SVC_NG, len = 0;

        MY_MEMSET(header, 0, sizeof(AIM_MDTG_HEADER_s));

        err = fseek(file_ptr, 0LL, SEEK_SET);
        if(err == SVC_OK){
            len = fread(header, 1, (UINT32)sizeof(AIM_MDTG_HEADER_s), file_ptr);
            err = (sizeof(AIM_MDTG_HEADER_s) == len) ? SVC_OK : SVC_NG;
        }

        if(err == SVC_OK){
            if(MY_STRNCMP(header->code, AIM_MDTG_HEADER_CODE, 4) == 0){
                err = SVC_OK;
            } else {
                err = SVC_NG;
            }
        }
    }
    printf("read_header < err=%d\n", err);
    return err;
}

int read_record(FILE* file_ptr, AIM_MDTG_RECORD_s* record)
{
    int err = SVC_NG;

    //printf("read_record > \n");
    if((file_ptr!=NULL) && (record!=NULL)){
        int err1=SVC_NG, len = 0;

        MY_MEMSET(record, 0, sizeof(AIM_MDTG_RECORD_s));

        len = fread(record, 1, (UINT32)sizeof(AIM_MDTG_RECORD_s), file_ptr);
        err = (sizeof(AIM_MDTG_RECORD_s) == len) ? SVC_OK : SVC_NG;
    }
    //printf("read_record < err=%d\n", err);
    return err;
}

int dump_header(AIM_MDTG_HEADER_s* obj)
{
    int err = SVC_NG;
    int i = 0;

    printf("dump_header > \n");
    if(obj != NULL){
        printf("	code = '%c%c%c%c' version=[%d] \n", obj->code[0], obj->code[1], obj->code[2], obj->code[3], obj->version);
        printf("	record_unit_size=[%d], base_odometer=[%d], trip_cnt=[%d]\n", obj->record_unit_size, obj->base_odometer, obj->trip_cnt);
        for(int i=0; i<obj->trip_cnt; i++) {
            printf("	offset[%d]=[%d]\n", i, obj->offset[i]);
        }

        printf("	slack_cnt=[%d], slack_unit_size=[%d]\n", obj->slack_cnt, obj->slack_unit_size);
        for(int i=0; i<obj->slack_cnt; i++) {
            printf("	slack[%d]=[%s]\n", i, obj->slack[i]);
        }
        err = SVC_OK;
    }
    printf("dump_header < err=%d\n", err);
    return err;
}

int dump_record(AIM_MDTG_RECORD_s* obj)
{
    int err = SVC_NG;

    printf("dump_record > \n");
    if(obj != NULL){
        printf("	approval_idx=[%d], serial_idx=[%d], vehicle_id_idx=[%d], vehicle_type=[%d], vehicle_plate_idx=[%d], provider_code_idx=[%d], driver_code_idx=[%d] \n",
            obj->approval_idx, obj->serial_idx, obj->vehicle_id_idx, obj->vehicle_type, obj->vehicle_plate_idx, obj->provider_code_idx, obj->driver_code_idx);
        printf("	odometerday=[%d], odometer=[%d] \n", obj->odometerday , obj->odometer );
        printf("	[%d/%d/%d, %d:%d:%d] \n",  obj->date.Year, obj->date.Month, obj->date.Day, obj->date.Hour, obj->date.Minute, obj->date.Second );
        printf("	vss_tick=[%d], rpm_tick=[%d] brake_pressure=[%d]\n", obj->vss_tick , obj->rpm_tick, obj->brake_pressure);
        printf("	latitude=[%d], longtitude=[%d] true_course=[%d]\n", obj->latitude , obj->longtitude, obj->true_course);
        printf("	accelx=[%.1f], accely=[%.1f] accelz=[%.1f]\n", obj->accelx , obj->accely, obj->accelz);
        err = SVC_OK;
    }
    printf("dump_record < err=%d\n", err);
    return err;
}

int dump_guide(void)
{
    int err = SVC_OK;
    printf("offset,tripid,approval,serial,vehicle_id,vehicle_type,vehicle_plate,provider_code,driver_code,odometerday,odometer,YYMMDD_HHMMSS,vss_tick,rpm_tick,brake_pressure,latitude,longtitude,true_course,accelx,accely,accelzz,dtc\n");
    return err;
}

int dump_convert_record(AIM_MDTG_HEADER_s* header, int offset, AIM_MDTG_RECORD_s* obj)
{
    int err = SVC_NG;

#if 0
    printf("dump_record > \n");
    if(obj != NULL){
        printf("	approval=[%s], serial=[%s], vehicle_id=[%s], vehicle_type=[%d], vehicle_plate=[%s], provider_code=[%s], driver_code=[%s] \n",
            header->slack[obj->approval_idx],
            header->slack[obj->serial_idx],
            header->slack[obj->vehicle_id_idx],
            obj->vehicle_type,
            header->slack[obj->vehicle_plate_idx],
            header->slack[obj->provider_code_idx],
            header->slack[obj->driver_code_idx]);
        printf("	odometerday=[%d], odometer=[%d] \n", obj->odometerday , obj->odometer );
        printf("	[%d/%d/%d, %d:%d:%d] \n",  obj->date.Year, obj->date.Month, obj->date.Day, obj->date.Hour, obj->date.Minute, obj->date.Second );
        printf("	vss_tick=[%d], rpm_tick=[%d] brake_pressure=[%d]\n", obj->vss_tick , obj->rpm_tick, obj->brake_pressure);
        printf("	latitude=[%d], longtitude=[%d] true_course=[%d]\n", obj->latitude , obj->longtitude, obj->true_course);
        printf("	accelx=[%.1f], accely=[%.1f] accelz=[%.1f]\n", obj->accelx , obj->accely, obj->accelz);
        err = SVC_OK;
    }
    printf("dump_record < err=%d\n", err);
#endif

    printf("%d,%d,%s,%s,%s,%d,%s,%s,%s,%d,%d,[%d/%02d/%02d_%02d:%02d:%02d],%04d,%04d,%d,%d,%d,%d,%06.1f,%06.1f,%06.1f,%d\n",
            offset,
            obj->id,
            header->slack[obj->approval_idx],
            header->slack[obj->serial_idx],
            header->slack[obj->vehicle_id_idx],
            obj->vehicle_type,
            header->slack[obj->vehicle_plate_idx],
            header->slack[obj->provider_code_idx],
            header->slack[obj->driver_code_idx],
            obj->odometerday,
            obj->odometer,
            obj->date.Year, obj->date.Month, obj->date.Day, obj->date.Hour, obj->date.Minute, obj->date.Second,
            obj->vss_tick, 
            obj->rpm_tick,
            obj->brake_pressure,
            obj->latitude, 
            obj->longtitude,
            obj->true_course,
            obj->accelx,
            obj->accely, 
            obj->accelz,
            obj->dtc);

    return err;
}

//===================================================================================
// system
//===================================================================================


int main(int argc, char* argv[])
{
    int err = 0, i=0;
    AIM_MDTG_HEADER_s header;
    AIM_MDTG_RECORD_s record;
    long pos = 0;

//	argc = 2;
//	argv[1]=(char *)"trip.tmp";

    if(argc == 2){
        char* fullpath = argv[1];
        FILE* file_ptr = fopen(fullpath, "rb");
        err = (file_ptr!=NULL) ? SVC_OK : SVC_NG;

        if(err == SVC_OK){
          err = read_header(file_ptr, &header);
          dump_header(&header);
        }

        if(err == SVC_OK){
            dump_guide();
            do {
                pos = ftell(file_ptr);
                err = read_record(file_ptr, &record);
                if(err == SVC_OK){
                    //dump_record(&record);
                    dump_convert_record(&header, pos, &record);
                }
            } while(err == SVC_OK);
        }

        if(file_ptr != NULL){
            fclose(file_ptr);
            file_ptr = NULL;
        }

    }
    return 0;
}


