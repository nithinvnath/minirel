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
 */

int OpenDB(int argc, char **argv) {
    DIR* dir_handler;
    char path[MAXPATH];

    if (argc < 2)
        return ErrorMsgs(ARGC_INSUFFICIENT, g_print_flag);

    if (g_db_open_flag == OK)
        return ErrorMsgs(DB_NOT_CLOSED, g_print_flag);

    if ((dir_handler = opendir(argv[1])) != NULL) {
        closedir(dir_handler);

        getcwd(g_invoked_directory, MAXPATH);

        g_db_open_flag = OK;

        chdir(argv[1]);

        if (OpenCats() == NOTOK) {
            g_print_flag = NOTOK;
            return NOTOK;
        }
    }/* database exists */
    else {
        return ErrorMsgs(DBNAME_INVALID, g_print_flag);
    }/* database directoy couldn't open */

    return OK;
}

