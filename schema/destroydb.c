
#include "../include/defs.h"
#include "../include/error.h"
#include "../include/globals.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <string.h>

/*
 * Function:  delete_file 
 * ----------------------
 * deletes an existing file
 *
 *  file_name: name of the file that has to be deleted
 *  db_name: name of the database
 *  
 *  returns: OK upon successful deletion of file.
 *           NOTOK: file does not exist
 */

int delete_file(char* file_name, char* db_name)
{
    char full_file_path[3 * RELNAME];

    sprintf(full_file_path,"%s/%s/%s",PATH,db_name,file_name);

    if(remove(full_file_path) == 0){
        return OK;
    } /* File deletion successful*/
    else{
        return NOTOK;
    } /* File does not exist*/

}

/*
 * Function:  delete_dir()
 * ------------------------
 * deletes an existing directory
 *
 *  dir_name: name of the directory that has to be deleted
 *  
 *  returns: OK    upon successful deletion of directory.
 *           NOTOK directory does not exist
 */

int delete_dir(char* dir_name)
{
    DIR *dir_handler;
    struct dirent *file_handler;

    char dir_path[2 * RELNAME + 2];
    sprintf(dir_path,"%s/%s",PATH,dir_name);

    if( (dir_handler = opendir(dir_path)) != NULL ){
        while ((file_handler = readdir (dir_handler)) != NULL) {
            delete_file(file_handler->d_name, dir_name);
        }
        closedir (dir_handler);
        rmdir(dir_path);
        return OK;
    } /* Directory could successfully deleted */
    else{
        return NOTOK;
    } /* Directory could not open */   
}

/*
 * Function:  DetroyDB()
 * ------------------------
 * deletes an existing directory
 *
 *  dir_name: name of the directory that has to be deleted
 *  
 *  returns: OK    upon successful deletion of directory.
 *           NOTOK directory does not exist
 */

int DestroyDB(int argc,char **argv)
{
    if(argc < 2)
        return ErrorMsgs(ARGC_INSUFFICIENT,g_print_flag);

    if(delete_dir(argv[1]) == NOTOK)
        return ErrorMsgs(DBNAME_INVALID,g_print_flag);

    /* DB and it's internal files have been destroyed*/
    return OK;
}