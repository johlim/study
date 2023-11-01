#include "AmbaTypes.h"
void aim_print_print_str5(UINT32 level, const char* module, const char *fmt, const char *arg1, const char *arg2, const char *arg3, const char *arg4, const char *arg5)
{
    printf(fmt,arg1,arg2,arg3,arg4,arg5);
    return;
}
UINT32 aim_file_tools_get_filesize(char* fullpath, UINT64* file_size)
{

    int size;

    FILE *fp = fopen(fullpath, "r");    // hello.txt 파일을 읽기 모드(r)로 열기.
                                           // 파일 포인터를 반환

    fseek(fp, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴
    size = ftell(fp);          // 파일 포인터의 현재 위치를 얻음

    printf("%d\n", size);      // 13

    fclose(fp);
    *file_size=size;
    return SVC_OK;
}
void aim_print_print_uint5(UINT16 level, const char* module, const char *fmt, UINT32 arg1, UINT32 arg2, UINT32 arg3, UINT32 arg4, UINT32 arg5)
{
    printf(fmt,arg1,arg2,arg3,arg4,arg5);
    return;
}
UINT32 AmbaFS_FileOpen(const char *pFileName, const char *pMode, AMBA_FS_FILE **pFile)
{
   *pFile= fopen(pFileName, "r");
   return SVC_OK;
}
UINT32 AmbaFS_FileClose(AMBA_FS_FILE *pFile)
{
   fclose(pFile);
   return SVC_OK;
}
UINT32 AmbaFS_FileRead(void *pBuf, UINT32 Size, UINT32 Count, AMBA_FS_FILE *pFile, UINT32 *pNumSuccess)
{
   *pNumSuccess = fread(pBuf, Size, Count,pFile);
   return SVC_OK;
}
UINT32 AmbaUtility_StringPrintUInt32(char *pBuffer, UINT32 BufferSize, const char *pFmtString, UINT32 Count, const UINT32 *pArgs)
{
    snprintf(pBuffer, BufferSize, pFmtString, Count, pArgs);
}
char aim_toupper(char c)
{
    char ret = c;
    if('a' <= c && c <= 'z') {
        ret = c - 32;
    }
    return ret;
}

char* aim_toupper_str(char* str)
{
    UINT32 len = strlen(str);
    UINT32 i = 0;
    for(i=0; i<len; i++){
        str[i] = aim_toupper(str[i]);
    }
    return str;
}