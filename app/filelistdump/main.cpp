#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "dcadump.h"

AIM_SCAN_HEADER_s fileheader;
AIM_SCAN_RECORD_s filebody;
static void make_header(void)
{
    // make dump
    fileheader.code[0]='s';
    fileheader.code[1]='c';
    fileheader.code[2]='a';
    fileheader.code[3]='n';
    fileheader.version=0;
    memset(&(fileheader.reserved[0]),0, 20);
}

static void make_body(unsigned int index)
{
    sprintf(filebody.filename,"%s%02d%s","/AIDDCA/adas/2022/06/30/adas_AR9DEV0310_20220630_0836", index %60, "_806.aiddca");
    filebody.filesize = index;
    filebody.allocatesize = index*64*1024;
    if (( index % 100 )==0) 
        filebody.isdir = 1;
    else
        filebody.isdir = 0;

    filebody.modifiedtime.Year=2022;
    filebody.modifiedtime.Month=6;
    filebody.modifiedtime.Day=30;
    filebody.modifiedtime.Hour=8;
    filebody.modifiedtime.Minute=36;
    filebody.modifiedtime.Second=index % 60;
}

int main(void)
{
    uint32_t i=0;
    FILE* fp = fopen("./sandbag.bin", "wb");

    // printf("size of AIM_SCAN_RECORD_s is (%ld)", sizeof(AIM_SCAN_RECORD_s));
    make_header();
    fwrite((const void *)&fileheader,1, sizeof(AIM_SCAN_HEADER_s), fp);

    for(i=1; i < 60; i++)
    {
        make_body(i);
        fwrite((const void *)&filebody,1, sizeof(AIM_SCAN_RECORD_s), fp);
    }
    fclose(fp);

    return 0;
}