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

int main(){
    strcpy(g_db_name,"sample_db");
//    OpenCats();
//    printf("%d\n",FindRelNum("relcat"));

    CloseRel(1);

//    printf("%d\n",OpenRel("abc"));
   return 0;
}
