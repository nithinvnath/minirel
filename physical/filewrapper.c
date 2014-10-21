#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define PATH ".minirel_data"
#define NAME_MAX_LENGTH 50

/*
A wrapper to all C - I/O library calls to be used by Page Routines.
*/

/*
 * Function:  create_file 
 * ----------------------
 * creates a new file
 *
 *  file_name: name of the file that is to be created
 *  db_name: name of the database
 *  
 *  returns: 0 upon successful creation of file.
 *           error code otherwise
 *           100: file already exists
 */

int create_file(char* file_name, char* db_name)
{
    FILE *file_pointer;
    char dir_path[2 * NAME_MAX_LENGTH];
    char full_file_path[3 * NAME_MAX_LENGTH];

    sprintf(full_file_path,"%s/%s/%s",PATH,db_name,file_name);
    
    
    if( access(full_file_path, F_OK) != -1){
        return 100;
    } /* File exists*/

    /* Create the main directory minirel_data if not present. */
    mkdir(PATH,0777);

    /* Create the database folder if not present. */
    sprintf(dir_path,"%s/%s",PATH,db_name);
    mkdir(dir_path,0777);
    
    file_pointer = fopen(full_file_path,"wb");
    //printf("%s\n",full_file_path);
    fclose(file_pointer);

    return 0;
}

int main(){
    create_file("xyz","test");
    create_file("xyz","test");
    return 0;
}