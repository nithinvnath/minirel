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
#include "../include/createdb.h"
#include "../include/print.h"
#include "../include/closedb.h"
#include "../include/create.h"

int main(int argc, char** argv){
    g_print_flag = 1;
    CreateDB(argc, argv);
    OpenDB(argc, argv);
    char **argument;
    argument = malloc(sizeof(char *)* 4);
    argument[1] = malloc(sizeof(char) * 10);
    argument[2] = malloc(sizeof(char) * 10);
    argument[3] = malloc(sizeof(char) * 10);
    strcpy(argument[1],"person");
    strcpy(argument[2],"name");
    strcpy(argument[3],"i");
    Create(4,argument);

    argument[0] = malloc(sizeof(char) * 100);
    getcwd(argument[0],MAXPATH);
    printf("%s\n",argument[0]);
    CloseDB(1,argv);

//    DestroyDB(argc, argv);
//    strcpy(g_db_name,"sample_db");
//    CreateCats();
//    OpenCats();
//    printf("relcat found at cache slot #%d\n",FindRelNum("relcat"));
//    printf("attrcat found at cache slot #%d\n",FindRelNum("attrcat"));
//    CloseCats();
//    CloseRel(1);

    return 0;
}
/*
    CreateDB(argc, argv);
    char **argument;
    argument = malloc(sizeof(char *)* 2);
    argument[1] = malloc(sizeof(char)*10);
    OpenDB(argc, argv);
    strcpy(argument[1], "relcat");
    Print(2,argument);
    printf("\n");
    strcpy(argument[1], "attrcat");
    Print(2,argument);
    CloseDB(2,argument);
*/