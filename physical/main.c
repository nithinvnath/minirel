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
#include "../include/insert.h"
#include "../include/destroy.h"

int main(int argc, char** argv){
    g_print_flag = 1;
    CreateDB(argc, argv);
    OpenDB(argc, argv);

    char **argument;
    argument = malloc(sizeof(char *)* 4);
    argument[0] = malloc(sizeof(char) * 10);
    argument[1] = malloc(sizeof(char) * 10);
    argument[2] = malloc(sizeof(char) * 10);
    argument[3] = malloc(sizeof(char) * 10);

    strcpy(argument[0],"create");
    strcpy(argument[1],"person");
    strcpy(argument[2],"name");
    strcpy(argument[3],"s20");
    Create(4,argument);

    strcpy(argument[0],"insert");
    strcpy(argument[1],"person");
    strcpy(argument[2],"name");
    strcpy(argument[3],"\"Dheeraj\"");
    Insert(4,argument);
    strcpy(argument[3],"\"Nithin\"");
    Insert(4,argument);

    strcpy(argument[0], "destroy");
    strcpy(argument[1], "person" );
    Destroy(2,argument);

    strcpy(argument[1], "person");
    Print(2,argument);
    printf("\n");
    strcpy(argument[1], "relcat");
    Print(2,argument);
    printf("\n");
    strcpy(argument[1], "attrcat");
    Print(2,argument);

    CloseDB(1,argv);
    return 0;
}