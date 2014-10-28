#include "../include/filewrapper.h"

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
    char dir_path[2 * NAME_MAX_LENGTH + 1];
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
    fclose(file_pointer);

    return 0;
}

/*
 * Function:  delete_file 
 * ----------------------
 * deletes an existing file
 *
 *  file_name: name of the file that has to be deleted
 *  db_name: name of the database
 *  
 *  returns: 0 upon successful deletion of file.
 *           error code otherwise
 *           101: file does not exist
 */

int delete_file(char* file_name, char* db_name)
{
    char full_file_path[3 * NAME_MAX_LENGTH];

    sprintf(full_file_path,"%s/%s/%s",PATH,db_name,file_name);

    if(remove(full_file_path) == 0){
        return 0;
    } /* File deletion successful*/
    else{
        return 101;
    } /* File does not exist*/

}

/*
 * Function:  delete_dir
 * ----------------------
 * deletes an existing directory
 *
 *  dir_name: name of the directory that has to be deleted
 *  
 *  returns: 0 upon successful deletion of directory.
 *           error code otherwise
 *           102: directory does not exist
 */

int delete_dir(char* dir_name)
{
    DIR *dir_handler;
    struct dirent *file_handler;

    char dir_path[2 * NAME_MAX_LENGTH + 1];
    sprintf(dir_path,"%s/%s",PATH,dir_name);

    if( (dir_handler = opendir(dir_path)) != NULL ){
        while ((file_handler = readdir (dir_handler)) != NULL) {
            delete_file(file_handler->d_name, dir_name);
        }
        closedir (dir_handler);
        rmdir(dir_path);
        return 0;
    } /* Directory could successfully deleted */
    else{
        return 102;
    } /* Directory could not open */   
}

/*
 * Function:  append_to_file
 * ----------------------
 * appends given data to the given file
 *
 * file_name: name of the file to which data should be appended
 * dir_name: name of the directory in which file resides
 * data: the data, as a character pointer to an array
 * data_len: length of the data
 *  
 *  returns: 0 upon successful writing
 *           error code otherwise
 *           103: directory/file does not exist
 */

int append_to_file(char* file_name, char* dir_name, char* data, int data_len)
{
    FILE *file_pointer;
    char full_file_path[3 * NAME_MAX_LENGTH];

    sprintf(full_file_path,"%s/%s/%s",PATH,dir_name,file_name);

    if( access(full_file_path, F_OK) == -1){
         return 103;
    } /* File/Directory does not exist*/

    file_pointer = fopen(full_file_path,"ab+");
    fwrite(data,1,data_len,file_pointer);
    fclose(file_pointer);
    return 0;
}

/*
 * Function:  write_to_file
 * ----------------------
 * writes given data to the given file
 *
 * file_name: name of the file to which data should be written
 * dir_name: name of the directory in which file resides
 * offset: from where, in file, the data should be written
 * data: the data, as a character pointer to an array
 * data_len: length of the data
 *  
 *  returns: 0 upon successful writing
 *           error code otherwise
 *           104: directory/file does not exist
 */

int write_to_file(char* file_name, char* dir_name, long offset, char* data, int data_len)
{
    FILE *file_pointer;
    char full_file_path[3 * NAME_MAX_LENGTH];

    sprintf(full_file_path,"%s/%s/%s",PATH,dir_name,file_name);

    if( access(full_file_path, F_OK) == -1){
        return 104;
    } /* File/Directory does not exist*/

    file_pointer = fopen(full_file_path,"rb+");
    fseek(file_pointer, offset, SEEK_SET);
    fwrite(data, 1, data_len, file_pointer);
    fclose(file_pointer);
    return 0;
}

/*
 * Function:  read_from_file
 * ----------------------
 * reads a file and copy content to given character pointer
 *
 * file_name: name of the file to which data should be read
 * dir_name: name of the directory in which file resides
 * offset: from where, in file, the data should be read
 * data: the data, as a character pointer to an array
 * data_len: length of the data to be read
 *  
 *  returns: 0 upon successful reading
 *           error code otherwise
 *           105: directory/file does not exist
 *           106: EOF reached before reading given number of bytes
 */

int read_from_file(char* file_name, char* dir_name, long offset, char* data, int data_len)
{
    FILE *file_pointer;
    char full_file_path[3 * NAME_MAX_LENGTH];

    sprintf(full_file_path,"%s/%s/%s",PATH,dir_name,file_name);

    if( access(full_file_path, F_OK) == -1){
        return 105;
    } /* File/Directory does not exist*/

    file_pointer = fopen(full_file_path,"rb+");
    fseek(file_pointer, offset, SEEK_SET);
    if( fread(data, 1, data_len, file_pointer) != data_len ){
        return 106;
    } /* Error in reading, EOF reached */
    fclose(file_pointer);
    return 0;
}
