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
 *           NOTOK database does not exist
 */

int OpenDB (int argc, char **argv)
{
    DIR* dir_handler;

    if(argc < 2)
        return ErrorMsgs(ARGC_INSUFFICIENT,g_print_flag);

//    CloseDB(1,"closedb");

    char db_path[2 * RELNAME + 2];
    sprintf(db_path, "%s/%s", PATH, argv[1]);

    if( (dir_handler = opendir(db_path)) != NULL ){
        closedir(dir_handler);
 
        strcpy(g_db_name, argv[1]);

        if(OpenCats() == NOTOK)
            return NOTOK;
    }/* database exists */
    else{
        return ErrorMsgs(DBNAME_INVALID,g_print_flag);
    }/* database directoy couldn't open */

    return OK;
}


