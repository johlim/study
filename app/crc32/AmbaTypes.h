#ifndef _AMBATYPES_H
#define _AMBATYPES_H
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#define UINT32 unsigned int
#define UINT64 unsigned long long
#define UINT16 unsigned short
#define SVC_NG -1
#define SVC_OK 0
#define LOG_DEBUG 1
#define LOG_NOTICE 2
// #define NULL 0
#define MY_STRCMP       strcmp
#define AMBA_FS_FILE    FILE
void aim_print_print_str5(UINT32 level, const char* module, const char *fmt, const char *arg1, const char *arg2, const char *arg3, const char *arg4, const char *arg5);
void aim_print_print_uint5(UINT16 level, const char* module, const char *fmt, UINT32 arg1, UINT32 arg2, UINT32 arg3, UINT32 arg4, UINT32 arg5);
char* aim_toupper_str(char* str);
UINT32 AmbaUtility_StringPrintUInt32(char *pBuffer, UINT32 BufferSize, const char *pFmtString, UINT32 Count, const UINT32 *pArgs);
UINT32 aim_file_tools_get_filesize(char* fullpath, UINT64* file_size);
UINT32 AmbaFS_FileOpen(const char *pFileName, const char *pMode, AMBA_FS_FILE **pFile);
UINT32 AmbaFS_FileClose(AMBA_FS_FILE *pFile);
UINT32 AmbaFS_FileRead(void *pBuf, UINT32 Size, UINT32 Count, AMBA_FS_FILE *pFile, UINT32 *pNumSuccess);
#endif 