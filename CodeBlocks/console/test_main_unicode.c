#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>


#include "app_unicodeutil.h"
#define USE_KOREAN_DIR
#if defined(USE_KOREAN_DIR)
//unsigned short g_strProductName[22] = {0xCF54,0xC544,0xB85C,0xC9C1}; //L"ÄÚŸÆ·ÎÁ÷"
unsigned char g_strProductName[22] = {0xec,0xbd,0x94,0xec,0x95,0x84,0xeb,0xa1,0x9c,0xec,0xa7,0x81};
unsigned char g_strInfName[22] = {0xec,0x83,0x81,0xec,0x8b,0x9c,0xeb,0x85,0xb9,0xed,0x99,0x94};
unsigned char g_strEvtName[22] = {0xec,0xb6,0xa9,0xea,0xb2,0xa9,0xeb,0x85,0xb9,0xed,0x99,0x94};
unsigned char g_strParName[22] = {0xec,0xa3,0xbc,0xec,0xb0,0xa8,0xeb,0x85,0xb9,0xed,0x99,0x94};
unsigned char g_strMotName[22] = {0xeb,0xaa,0xa8,0xec,0x85,0x98,0xeb,0x85,0xb9,0xed,0x99,0x94};

#else
unsigned short g_strProductName[22] = {'C','O','R','E','L','O','G','I','C'};
#endif

int test_main(int argc, char * argv[])
{

    unsigned char strAscii[128]= {0,};
    unsigned short strUni[128]= {0,};
    unsigned char g_strdirpath[128]= {0,};
    int size=0;
    int i=0;

    if(argc >1)
    {

        printf("%s:\n", argv[1]);
        size = strlen(argv[1]);

        printf("%d:\n",size);

        for(i=0;i<size;i++)
        {
            int c;
            c= (int)argv[1][i];
        putchar(c);
        printf("%02x",c);

        }
        printf("\n%s\n", g_strProductName);
        PromoteASCIItoUNICODE((unsigned char *)argv[1],strUni);
                              printf("1 %s \n", strUni);
        DemoteUNICODEtoASCII(strUni, strAscii);
                              printf("2 %s \n", strAscii);

    }
    printf("* %s \n", g_strInfName);
    printf("* %s \n", g_strEvtName);
    printf("* %s \n", g_strParName);
    printf("* %s \n", g_strMotName);
#if 0
    mkdir((const char *)g_strInfName, S_IRWXU| S_IRGRP|S_IWGRP);
    perror("mkdir");
    mkdir((const char *)g_strEvtName, S_IRWXU|S_IRGRP|S_IWGRP);
    mkdir((const char *)g_strParName, S_IRWXU|S_IRGRP|S_IWGRP);
    mkdir((const char *)g_strMotName, S_IRWXU|S_IRGRP|S_IWGRP);
 #endif
    sprintf(( char *)g_strdirpath, "/media/G100/%s",g_strInfName);
    mkdir((const char *)g_strdirpath, S_IRWXU| S_IRGRP|S_IWGRP);
    sprintf(( char *)g_strdirpath, "/media/G100/%s",g_strEvtName);
    mkdir((const char *)g_strdirpath, S_IRWXU| S_IRGRP|S_IWGRP);
    sprintf(( char *)g_strdirpath, "/media/G100/%s",g_strParName);
    mkdir((const char *)g_strdirpath, S_IRWXU| S_IRGRP|S_IWGRP);
    sprintf(( char *)g_strdirpath, "/media/G100/%s",g_strMotName);
    mkdir((const char *)g_strdirpath, S_IRWXU| S_IRGRP|S_IWGRP);
    perror("mkdir");

    return 0;
}

int main(int argc, char * argv[])
{
    char * array={"a","b","c"};
    return test_main(argc,argv);

}
