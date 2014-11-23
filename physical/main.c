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
#include "../include/select.h"
#include "../include/project.h"
#include "../include/join.h"

int main(int argc, char** argv){

    g_print_flag = 1;
    CreateDB(argc, argv);
    OpenDB(argc, argv);

    char **argument;
    argument = malloc(sizeof(char *)* 10);
    argument[0] = malloc(sizeof(char) * 20);
    argument[1] = malloc(sizeof(char) * 20);
    argument[2] = malloc(sizeof(char) * 20);
    argument[3] = malloc(sizeof(char) * 20);
    argument[4] = malloc(sizeof(char) * 20);
    argument[5] = malloc(sizeof(char) * 20);
    argument[6] = malloc(sizeof(char) * 20);
    argument[7] = malloc(sizeof(char) * 20);

    strcpy(argument[0],"create");
    strcpy(argument[1],"student");
    strcpy(argument[2],"name");
    strcpy(argument[3],"s20");
    strcpy(argument[4],"SrNo");
    strcpy(argument[5],"i");
    strcpy(argument[6],"DeptID");
    strcpy(argument[7],"s5");
    Create(8,argument);

    strcpy(argument[0],"create");
    strcpy(argument[1],"dept");
    strcpy(argument[2],"name");
    strcpy(argument[3],"s20");
    strcpy(argument[4],"id");
    strcpy(argument[5],"s7");
    Create(6,argument);

    strcpy(argument[0],"insert");
    strcpy(argument[1],"student");
    strcpy(argument[2],"name");
    strcpy(argument[3],"\"Dheeraj\"");
    strcpy(argument[4],"SrNo");
    strcpy(argument[5],"11168");
    strcpy(argument[6],"DeptID");
    strcpy(argument[7],"\"CSA\"");
    Insert(8,argument);

    strcpy(argument[3],"\"Nithin\"");
    strcpy(argument[5],"11158");
    strcpy(argument[7],"\"CSA\"");    
    Insert(8,argument);

    strcpy(argument[3],"\"Imthiyas\"");
    strcpy(argument[5],"11127");
    strcpy(argument[7],"\"DESE\"");
    Insert(8,argument);

    strcpy(argument[0],"insert");
    strcpy(argument[1],"dept");
    strcpy(argument[2],"name");    
    strcpy(argument[3],"\"Computer Science\"");
    strcpy(argument[4],"id");
    strcpy(argument[5],"\"CSA\"");
    Insert(6,argument);

    strcpy(argument[3],"\"Electronics\"");
    strcpy(argument[5],"\"DESE\"");
    Insert(6,argument);

    strcpy(argument[0],"join");
    strcpy(argument[1],"output");
    strcpy(argument[2],"student");
    strcpy(argument[3],"DeptID");
    strcpy(argument[4],"dept");
    strcpy(argument[5],"id");    
    Join(6,argument);

    strcpy(argument[1], "output");
    Print(2,argument);
    printf("\n===================================================================================\n");
    strcpy(argument[1], "student");
    Print(2,argument);
    printf("\n===================================================================================\n");
    strcpy(argument[1], "dept");
    Print(2,argument);
    printf("\n===================================================================================\n");
    strcpy(argument[1], "relcat");
    Print(2,argument);
    printf("\n===================================================================================\n");
    strcpy(argument[1], "attrcat");
    Print(2,argument);

    CloseDB(1,argv);
    return 0;
}