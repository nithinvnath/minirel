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

int deleteFile(char* fileName, char* dbPath) {

    char fullFilePath[MAXPATH + RELNAME];

    sprintf(fullFilePath, "%s/%s", dbPath, fileName);

    if (remove(fullFilePath) == 0) {
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

int deleteDir(char* directoryPath) {
    DIR *directoryHandler;
    struct dirent *fileHandler;

    if ((directoryHandler = opendir(directoryPath)) != NULL) {
        while ((fileHandler = readdir(directoryHandler)) != NULL) {
            deleteFile(fileHandler->d_name, directoryPath);
        }
        closedir(directoryHandler);
        rmdir(directoryPath);
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
        return ErrorMsgs(ARGC_INSUFFICIENT, g_PrintFlag);

    if (g_DBOpenFlag == OK)
        return ErrorMsgs(DB_NOT_CLOSED, g_PrintFlag);

    if (deleteDir(argv[1]) == NOTOK)
        return ErrorMsgs(DBNAME_INVALID, g_PrintFlag);

    /* DB and it's internal files have been destroyed*/
    return OK;
}
