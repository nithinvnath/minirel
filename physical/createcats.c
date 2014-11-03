/*
 * createcats.c
 *
 *  Created on: 31-Oct-2014
 *      Author: Dheeraj
 */

#include<stdio.h>
#include "../include/createcats.h"

/*
 * Function: CreateRelCat() 
 * ----------------------
 * Creates relcat catalog file
 *
 *  returns: OK on success
 *           NOTOK on failure
 */

int CreateRelCat()
{
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

    //Slotmap for Page 1
    convertIntToByteArray(0xC0000000, content); 

    strncpy(content + PAGESIZE - MAXRECORD,"relcat",6);   

    convertIntToByteArray(40, content + 20 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(12, content + 24 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(6, content + 28 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(2, content + 32 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(1, content + 36 + PAGESIZE - MAXRECORD);

    strncpy(content + 40 + PAGESIZE - MAXRECORD,"attrcat",7);

    convertIntToByteArray(52, content + 20 +40 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(9, content + 24 +40 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(5, content + 28 +40 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(11, content + 32 +40 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(2, content + 36 +40 + PAGESIZE - MAXRECORD);

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
<<<<<<< HEAD
CreateCats() {
    extern char *g_db_name;
    create_file(RELATION_CATALOG_NAME,g_db_name);
=======
>>>>>>> dheeraj

int CreateAttrCat()
{
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

    //Slotmap for Page 1
    convertIntToByteArray(0xFF800000, content); 

    convertIntToByteArray(0,     content + 0 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(20,    content + 4 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(STRING,content + 8 + PAGESIZE - MAXRECORD);
    strncpy(content + 12 + PAGESIZE - MAXRECORD,"relName",7);
    strncpy(content + 32 + PAGESIZE - MAXRECORD,"relcat",6);

    convertIntToByteArray(20,      content + 0 + 52 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(4,       content + 4 + 52 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(INTEGER, content + 8 + 52 + PAGESIZE - MAXRECORD);
    strncpy(content + 12 + 52 + PAGESIZE - MAXRECORD,"recLength",9);
    strncpy(content + 32 + 52 + PAGESIZE - MAXRECORD,"relcat",6);

    convertIntToByteArray(24,      content + 0 + 52*2 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(4,       content + 4 + 52*2 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(INTEGER, content + 8 + 52*2 + PAGESIZE - MAXRECORD);
    strncpy(content + 12 + 52*2 + PAGESIZE - MAXRECORD,"recsPerPg",9);
    strncpy(content + 32 + 52*2 + PAGESIZE - MAXRECORD,"relcat",6);

    convertIntToByteArray(28,      content + 0 + 52*3 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(4,       content + 4 + 52*3 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(INTEGER, content + 8 + 52*3 + PAGESIZE - MAXRECORD);
    strncpy(content + 12 + 52*3 + PAGESIZE - MAXRECORD,"numAttrs",8);
    strncpy(content + 32 + 52*3 + PAGESIZE - MAXRECORD,"relcat",6);

    convertIntToByteArray(32,      content + 0 + 52*4 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(4,       content + 4 + 52*4 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(INTEGER, content + 8 + 52*4 + PAGESIZE - MAXRECORD);
    strncpy(content + 12 + 52*4 + PAGESIZE - MAXRECORD,"numRecs",7);
    strncpy(content + 32 + 52*4 + PAGESIZE - MAXRECORD,"relcat",6);

    convertIntToByteArray(36,      content + 0 + 52*5 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(4,       content + 4 + 52*5 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(INTEGER, content + 8 + 52*5 + PAGESIZE - MAXRECORD);
    strncpy(content + 12 + 52*5 + PAGESIZE - MAXRECORD,"numPgs",6);
    strncpy(content + 32 + 52*5 + PAGESIZE - MAXRECORD,"relcat",6);

    convertIntToByteArray(0,       content + 0 + 52*6 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(4,       content + 4 + 52*6 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(INTEGER, content + 8 + 52*6 + PAGESIZE - MAXRECORD);
    strncpy(content + 12 + 52*6 + PAGESIZE - MAXRECORD,"offset",6);
    strncpy(content + 32 + 52*6 + PAGESIZE - MAXRECORD,"attrcat",7);

    convertIntToByteArray(4,       content + 0 + 52*7 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(4,       content + 4 + 52*7 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(INTEGER, content + 8 + 52*7 + PAGESIZE - MAXRECORD);
    strncpy(content + 12 + 52*7 + PAGESIZE - MAXRECORD,"length",6);
    strncpy(content + 32 + 52*7 + PAGESIZE - MAXRECORD,"attrcat",7);

    convertIntToByteArray(8,       content + 0 + 52*8 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(4,       content + 4 + 52*8 + PAGESIZE - MAXRECORD);
    convertIntToByteArray(INTEGER, content + 8 + 52*8 + PAGESIZE - MAXRECORD);
    strncpy(content + 12 + 52*8 + PAGESIZE - MAXRECORD,"type",4);
    strncpy(content + 32 + 52*8 + PAGESIZE - MAXRECORD,"attrcat",7);
 
    //New Page
    //Slotmap for Page 2 
    convertIntToByteArray(0xC0000000, content + PAGESIZE); 

    convertIntToByteArray(12,      content + 0 + PAGESIZE*2 - MAXRECORD);
    convertIntToByteArray(20,      content + 4 + PAGESIZE*2 - MAXRECORD);
    convertIntToByteArray(STRING,  content + 8 + PAGESIZE*2 - MAXRECORD);
    strncpy(content + 12 + PAGESIZE*2 - MAXRECORD,"attrName",8);
    strncpy(content + 32 + PAGESIZE*2 - MAXRECORD,"attrcat",7);

    convertIntToByteArray(12,      content + 0 + PAGESIZE*2 - MAXRECORD);
    convertIntToByteArray(20,      content + 4 + PAGESIZE*2 - MAXRECORD);
    convertIntToByteArray(STRING,  content + 8 + PAGESIZE*2 - MAXRECORD);
    strncpy(content + 12 + PAGESIZE*2 - MAXRECORD,"relName",7);
    strncpy(content + 32 + PAGESIZE*2 - MAXRECORD,"attrcat",7);

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
