#include <stdint.h>
uint32_t aim_crc_tools_verify_file(char* fullpath, char* crc);
int main(void)
{
    int i;
    uint32_t ret;
    char crcin[128]="652141fe";

    for (i=0; i<10;i++)
    ret = aim_crc_tools_verify_file("AP_UPDATE_ROADSCOPE9_HW005_V0.5.2j_652141fe.BIN", crcin);

    return 0;
}