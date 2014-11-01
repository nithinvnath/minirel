/*
 * createcats.c
 *
 *  Created on: 31-Oct-2014
 *      Author: Dheeraj
 */

#include "../include/createcats.h"

/*
 * Function: CreateRelCat() 
 * ----------------------
 * Creates relcat catalog file
 *
 *  returns: OK on success
 *           NOTOK on failure
 */

int CreateRelCat(){
    FILE *file_pointer;
    char full_file_path[3 * RELNAME];
    char content[PAGESIZE];
    int i;

    for(i=0; i<PAGESIZE; i++)
        content[i] = 0;

    sprintf(full_file_path,"%s/%s/%s",PATH,g_db_name,"relcat");
    
    if( access(full_file_path, F_OK) != -1){
        ErrorMsgs(CAT_FILE_ALREADY_EXIST);
        return NOTOK;
    } /* Catalog Files Exists */
    
    file_pointer = fopen(full_file_path,"wb");

    strncpy(content,"relcat",6);

    convertIntToByteArray(40, content + 20);
    convertIntToByteArray(12, content + 24);
    convertIntToByteArray(6, content + 28);
    convertIntToByteArray(2, content + 32);
    convertIntToByteArray(1, content + 36);

    strncpy(content + 40,"attrcat",7);

    convertIntToByteArray(52, content + 20 +40);
    convertIntToByteArray(9, content + 24 +40);
    convertIntToByteArray(5, content + 28 +40);
    convertIntToByteArray(11, content + 32 +40);
    convertIntToByteArray(2, content + 36 +40);

    fwrite(content,1,PAGESIZE,file_pointer);

    fclose(file_pointer);
    return OK;
}

/*
 * Function: CreateRelCat() 
 * ----------------------
 * Creates relcat catalog file
 *
 *  returns: OK on success
 *           NOTOK on failure
 */

int CreateAttrCat(){
    FILE *file_pointer;
    char full_file_path[3 * RELNAME];
    char content[PAGESIZE*2];
    int i;

    for(i=0; i<PAGESIZE*2; i++)
        content[i] = 0;

    sprintf(full_file_path,"%s/%s/%s",PATH,g_db_name,"attrcat");
    
    if( access(full_file_path, F_OK) != -1){
        ErrorMsgs(CAT_FILE_ALREADY_EXIST);
        return NOTOK;
    } /* Catalog Files Exists */
    
    file_pointer = fopen(full_file_path,"wb");

    convertIntToByteArray(0,     content + 0);
    convertIntToByteArray(20,    content + 4);
    convertIntToByteArray(STRING,content + 8);
    strncpy(content + 12,"relName",7);
    strncpy(content + 32,"relcat",6);

    convertIntToByteArray(20,      content + 0 + 52);
    convertIntToByteArray(4,       content + 4 + 52);
    convertIntToByteArray(INTEGER, content + 8 + 52);
    strncpy(content + 12 + 52,"recLength",9);
    strncpy(content + 32 + 52,"relcat",6);

    convertIntToByteArray(24,      content + 0 + 52*2);
    convertIntToByteArray(4,       content + 4 + 52*2);
    convertIntToByteArray(INTEGER, content + 8 + 52*2);
    strncpy(content + 12 + 52*2,"recsPerPg",9);
    strncpy(content + 32 + 52*2,"relcat",6);

    convertIntToByteArray(28,      content + 0 + 52*3);
    convertIntToByteArray(4,       content + 4 + 52*3);
    convertIntToByteArray(INTEGER, content + 8 + 52*3);
    strncpy(content + 12 + 52*3,"numAttrs",8);
    strncpy(content + 32 + 52*3,"relcat",6);

    convertIntToByteArray(32,      content + 0 + 52*4);
    convertIntToByteArray(4,       content + 4 + 52*4);
    convertIntToByteArray(INTEGER, content + 8 + 52*4);
    strncpy(content + 12 + 52*4,"numRecs",7);
    strncpy(content + 32 + 52*4,"relcat",6);

    convertIntToByteArray(36,      content + 0 + 52*5);
    convertIntToByteArray(4,       content + 4 + 52*5);
    convertIntToByteArray(INTEGER, content + 8 + 52*5);
    strncpy(content + 12 + 52*5,"numPgs",6);
    strncpy(content + 32 + 52*5,"relcat",6);

    convertIntToByteArray(0,       content + 0 + 52*6);
    convertIntToByteArray(4,       content + 4 + 52*6);
    convertIntToByteArray(INTEGER, content + 8 + 52*6);
    strncpy(content + 12 + 52*6,"offset",6);
    strncpy(content + 32 + 52*6,"attrcat",7);

    convertIntToByteArray(4,       content + 0 + 52*7);
    convertIntToByteArray(4,       content + 4 + 52*7);
    convertIntToByteArray(INTEGER, content + 8 + 52*7);
    strncpy(content + 12 + 52*7,"length",6);
    strncpy(content + 32 + 52*7,"attrcat",7);

    convertIntToByteArray(8,       content + 0 + 52*8);
    convertIntToByteArray(4,       content + 4 + 52*8);
    convertIntToByteArray(INTEGER, content + 8 + 52*8);
    strncpy(content + 12 + 52*8,"type",4);
    strncpy(content + 32 + 52*8,"attrcat",7);

    convertIntToByteArray(12,      content + 0 + 52*9);
    convertIntToByteArray(20,      content + 4 + 52*9);
    convertIntToByteArray(STRING,  content + 8 + 52*9);
    strncpy(content + 12 + 52*9,"attrName",8);
    strncpy(content + 32 + 52*9,"attrcat",7);

    convertIntToByteArray(12,      content + 0 + 52*10);
    convertIntToByteArray(20,      content + 4 + 52*10);
    convertIntToByteArray(STRING,  content + 8 + 52*10);
    strncpy(content + 12 + 52*10,"relName",7);
    strncpy(content + 32 + 52*10,"attrcat",7);

    fwrite(content,1,PAGESIZE*2,file_pointer);   

    fclose(file_pointer);
    return OK;
}

/*
 * Function: CreateCats() 
 * ----------------------
 * Creates the system catalogs and places entries in the catalogs for the catalogs
 *
 *  returns: OK on success
 *           NOTOK on failure
 */

int CreateCats() 
{ 
    if( CreateRelCat() == NOTOK || CreateAttrCat() == NOTOK )
        return NOTOK;
    else
        return OK;
}
