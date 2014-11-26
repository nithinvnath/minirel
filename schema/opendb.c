/*
 * createcats.c
 *
 *  Created on: 5-Nov-2014
 *      Author: Dheeraj
 */

#include "../include/opendb.h"

/*
 * Function: OpenDB()
 * ------------------------
 * changes the working directory to be the database directory, opens the catalogs and initializes 
 * the various global data structures
 *
 * argv[0] = “opendb”
 * argv[1] = database name
 * argv[argc] = NIL
 *
 *  returns: OK    upon opening database
 *           NOTOK database does not exist, or unable to open catalog
 *
 * GLOBAL VARIABLES MODIFIED:
 *      g_InvokedDirectory is assigned with invoked location of minirel.
 *      g_DBOpenFlag = OK
 *
 * ERRORS REPORTED:
 *      ARGC_INSUFFICIENT
 *      DB_NOT_CLOSED
 *      DBNAME_INVALID
 *
 * ALGORITHM:
 *   1. Checks for Errors.
 *   2. copies current directory to g_InvokedDirectoy
 *   3. changes to given database directory and Open cats.
 *   
 * IMPLEMENTATION NOTES:
 *      Uses OpenCats from physical layer.
 *
 */

int OpenDB(int argc, char **argv) {
    DIR* directoryHandler;
    char path[MAXPATH];

    if (argc < 2)
        return ErrorMsgs(ARGC_INSUFFICIENT, g_PrintFlag);

    if (g_DBOpenFlag == OK)
        return ErrorMsgs(DB_NOT_CLOSED, g_PrintFlag);

    if ((directoryHandler = opendir(argv[1])) != NULL) {
        closedir(directoryHandler);

        getcwd(g_InvokedDirectory, MAXPATH);

        g_DBOpenFlag = OK;

        chdir(argv[1]);

        if (OpenCats() == NOTOK) {
            g_PrintFlag = NOTOK;
            return NOTOK;
        }
    }/* database exists */
    else {
        return ErrorMsgs(DBNAME_INVALID, g_PrintFlag);
    }/* database directoy couldn't open */

    return OK;
}

