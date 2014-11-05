#include <stdio.h>
#include <string.h>

#include "../include/buffer.h"
#include "../include/cache.h"
#include "../include/defs.h"
#include "../include/error.h"
#include "../include/findrec.h"
#include "../include/flushpage.h"
#include "../include/getnextrec.h"
#include "../include/globals.h"
#include "../include/helpers.h"
#include "../include/readpage.h"
#include "../include/opencats.h"
#include "../include/openrel.h"
#include "../include/findrelnum.h"
#include "../include/closerel.h"
#include "../include/createcats.h"
#include "../include/closecats.h"
#include "../include/destroydb.h"
#include "../include/opendb.h"

int main(int argc, char** argv){
    g_print_flag = 1;
    OpenDB(argc, argv);
//    DestroyDB(argc, argv);
//    strcpy(g_db_name,"sample_db");
//    CreateCats();
//    OpenCats();
    printf("relcat found at cache slot #%d\n",FindRelNum("relcat"));
    printf("attrcat found at cache slot #%d\n",FindRelNum("attrcat"));
    CloseCats();
//    CloseRel(1);

    // char bin_data[4];
    // float val;
    // printf("Enter a float number: ");
    // scanf("%f",&val);
    // convertFloatToByteArray(val, bin_data);
    // printf("Binary data: %x %x %x %x\n",bin_data[0], bin_data[1], bin_data[2], bin_data[3]);
    // printf("Original data: %f\nConvertd data: %f\n",val,readFloatFromByteArray(bin_data,0));
    return 0;
}
