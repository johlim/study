#include <barcode.h>

int
main(int argc, char* argv[])
{
    struct Barcode_Item * bcode = Barcode_Create (argv[1]);
    FILE * fp = fopen(argv[2], "w");
    Barcode_Encode(bcode, BARCODE_ISBN);
    Barcode_Print(bcode, fp, BARCODE_OUT_EPS);
    fclose(fp);
    Barcode_Delete(bcode);

    return 0;

}
