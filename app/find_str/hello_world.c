#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WIFI_CONF "./plk_factory_wifi.cfg"

int findValue(char *strInput, const char *strTarget)
{
    int intResult=0;

    int i = 0;
    int nCount = 0;
    int nTargetLength = strlen(strTarget);
 

    while (*strInput)
    {
        if (memcmp(strInput, strTarget, nTargetLength) == 0)
        {
            //  Found
            intResult++;
            return intResult;
        }
        else
        {
            strInput++;
        }
    }
 
    return intResult;
}

#define MAX_STR_LENGTH (128)

int main(int argc, char ** argv)
{
    FILE * p_file=NULL;
    char strbuf[MAX_STR_LENGTH]={0,};
    int is_changed=0;

    p_file = fopen(WIFI_CONF, "r");
    if (p_file)
    {

        while ( fgets(strbuf,MAX_STR_LENGTH,p_file) != NULL) {
            int ret=0;
            ret =findValue(strbuf,"mode=1");

            if (ret != 0)
            {

                printf("%s",strbuf);
                break;

            }

            // ret =findValue(strbuf,"AP_SSID=AIMATICS","AP_SSID=AR9DEV0000",&is_changed);

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