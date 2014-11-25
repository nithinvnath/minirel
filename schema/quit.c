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
 * GLOBAL VARIABLES MODIFIED:
 *      <None>
 *
 * ERRORS REPORTED:
 *      <None>
 *
 * ALGORITHM:
 *   1. If database is not closed, call CloseDB
 *   2. Frees up allocated locations
 *
 * IMPLEMENTATION NOTES:
 *      Uses CloseDB from schema layer.
 */

void Quit(int argc, char **argv) {
    char **closeDBArguments;
    closeDBArguments = malloc(sizeof(char *));
    *closeDBArguments = malloc(sizeof(char) * 10);

    strcpy(closeDBArguments[0], "closedb");

    if (g_DBOpenFlag == OK)
        CloseDB(1, closeDBArguments);

    free(*closeDBArguments);
    free(closeDBArguments);

}

