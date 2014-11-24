/*
 * createcats.c
 *
 *  Created on: 5-Nov-2014
 *      Author: Dheeraj
 */

#include "../include/destroydb.h"

/*
 * Function:  delete_file() 
 * ------------------------
 * deletes an existing file
 *
 *  file_name: name of the file that has to be deleted
 *  db_path: name and address of the database
 *  
 *  returns: OK upon successful deletion of file.
 *           NOTOK: file does not exist
 */

int delete_file(char* file_name, char* db_path) {

    char full_file_path[MAXPATH + RELNAME];

    sprintf(full_file_path, "%s/%s", db_path, file_name);

    if (remove(full_file_path) == 0) {
        return OK;
    } /* File deletion successful*/
    else {
        return NOTOK;
    } /* File does not exist*/
}

/*
 * Function:  delete_dir()
 * ------------------------
 * deletes an existing directory
 *
 *  dir_path: name and address of the directory that has to be deleted
 *  
 *  returns: OK    upon successful deletion of directory.
 *           NOTOK directory does not exist
 */

int delete_dir(char* dir_path) {
    DIR *dir_handler;
    struct dirent *file_handler;

    if ((dir_handler = opendir(dir_path)) != NULL) {
        while ((file_handler = readdir(dir_handler)) != NULL) {
            delete_file(file_handler->d_name, dir_path);
        }
        closedir(dir_handler);
        rmdir(dir_path);
        return OK;
    } /* Directory could successfully deleted */
    else {
        return NOTOK;
    } /* Directory could not open */
}

/*
 * Function:  DetroyDB()
 * ------------------------
 * deletes an existing database
 *
 * argv[0] = “destroydb”
 * argv[1] = database name
 * argv[argc] = NIL
 * 
 * returns: OK    upon successful deletion of directory.
 *          NOTOK directory does not exist
 */

int DestroyDB(int argc, char **argv) {
    if (argc < 2)
        return ErrorMsgs(ARGC_INSUFFICIENT, g_print_flag);

    if (g_db_open_flag != 0)
        return ErrorMsgs(DB_NOT_CLOSED, g_print_flag);

    if (delete_dir(argv[1]) == NOTOK)
        return ErrorMsgs(DBNAME_INVALID, g_print_flag);

    /* DB and it's internal files have been destroyed*/
    return OK;
}
