#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WIFI_CONF "./wifi.conf"

char *replaceValue(char *strInput, const char *strTarget, const char *strChange , int * pCount)
{
    char* strResult;
    char* strTemp;
    int i = 0;
    int nCount = 0;
    int nTargetLength = strlen(strTarget);
 
    if (nTargetLength < 1)
        return strInput;
 
    int nChangeLength = strlen(strChange);
 
    if (nChangeLength != nTargetLength)
    {
        for (i = 0; strInput[i] != '\0';)
        {
            if (memcmp(&strInput[i], strTarget, nTargetLength) == 0)
            {
                nCount++;
                i += nTargetLength;
            }
            else i++;
        }
    }
    else
    {
        i = strlen(strInput);
    }
 
    strResult = (char *) malloc(i + 1 + nCount * (nChangeLength - nTargetLength));
    if (strResult == NULL) return NULL;
 
 
    strTemp = strResult;
    while (*strInput)
    {
        if (memcmp(strInput, strTarget, nTargetLength) == 0)
        {
            memcpy(strTemp, strChange, nChangeLength);
            strTemp += nChangeLength;
            strInput  += nTargetLength;
        }
        else
        {
            *strTemp++ = *strInput++;
        }
    }
 
    *strTemp = '\0';
    *pCount=nCount;
    return strResult;
}

#define MAX_STR_LENGTH (128)

int main(int argc, char ** argv)
{
    FILE * p_file=NULL;
    char strbuf[MAX_STR_LENGTH]={0,};
    int is_changed=0;

    p_file = fopen(WIFI_CONF, "r+");
    if (p_file)
    {

        while ( fgets(strbuf,MAX_STR_LENGTH,p_file) != NULL) {
            char * ret=NULL;
            ret =replaceValue(strbuf,"WIFI_MODE=sta","WIFI_MODE=ap",&is_changed);

            if (ret != NULL)
            {
                if (is_changed)
                {
                    printf(strbuf);
                    printf(ret);
                } 
                free(ret);
            }

            // ret =replaceValue(strbuf,"AP_SSID=AIMATICS","AP_SSID=AR9DEV0000",&is_changed);

            // if (ret != NULL)
            // {
            //     if (is_changed)
            //     {
            //         printf(strbuf);
            //         printf(ret);
            //     } 
            //     free(ret);
            // }
            memset(strbuf,0,MAX_STR_LENGTH);
        }

        fclose(p_file);

    }
    return 0;
}