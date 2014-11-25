/*
 * createcats.c
 *
 *  Created on: 7-Nov-2014
 *      Author: Dheeraj
 */

#include "../include/quit.h"

/*
 * Function:  Quit()
 * ------------------------
 * terminates the program after closing database, if open
 *
 * argv[0] = “quit”
 * argv[argc] = NIL
 * 
 */

void Quit(int argc, char **argv) {
    char **arg_closedb;
    arg_closedb = malloc(sizeof(char *));
    *arg_closedb = malloc(sizeof(char) * 10);

    strcpy(arg_closedb[0], "closedb");

    if (g_db_open_flag == OK)
        CloseDB(1, arg_closedb);

    free(*arg_closedb);
    free(arg_closedb);

}

