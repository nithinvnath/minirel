/*
 *  opencats.c
 *
 *  Created on: 30-Oct-2014
 *      Author: Dheeraj
 */


#include "../include/globals.h"
#include "../include/defs.h"
#include "../include/cache.h"
#include "../include/buffers.h"
#include "../include/globals.h"
#include "../include/readpage.h"
#include "../include/helpers.h"


/*
 * Function:  create_attr_cat_relcat
 * ----------------------------------
 *  create linkedlist form of attr_cat of relcat relation
 *  
 *  returns: pointer to the head of linkedlist
 */

struct attrCatalog* create_attr_cat_relcat(){

    struct attrCatalog *temp, *newnode; 

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 36;
    (*newnode).length = 4;
    (*newnode).type   = 'i';
    strcpy( (*newnode).attrName, "numPgs");
    strcpy( (*newnode).relName,  "relcat");
    (*newnode).next = NULL;
    temp = newnode;

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 32;
    (*newnode).length = 4;
    (*newnode).type   = 'i';
    strcpy( (*newnode).attrName, "numRecs");
    strcpy( (*newnode).relName,  "relcat");
    (*newnode).next = temp;
    temp = newnode;

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 28;
    (*newnode).length = 4;
    (*newnode).type   = 'i';
    strcpy( (*newnode).attrName, "numAttrs");
    strcpy( (*newnode).relName,  "relcat");
    (*newnode).next = NULL;
    temp = newnode;

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 24;
    (*newnode).length = 4;
    (*newnode).type   = 'i';
    strcpy( (*newnode).attrName, "recsPerPg");
    strcpy( (*newnode).relName,  "relcat");
    (*newnode).next = NULL;
    temp = newnode;

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 20;
    (*newnode).length = 4;
    (*newnode).type   = 'i';
    strcpy( (*newnode).attrName, "recLength");
    strcpy( (*newnode).relName,  "relcat");
    (*newnode).next = NULL;
    temp = newnode;

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 0;
    (*newnode).length = 20;
    (*newnode).type   = 's';
    strcpy( (*newnode).attrName, "relName");
    strcpy( (*newnode).relName,  "relcat");
    (*newnode).next = NULL;
    temp = newnode;

    return temp;
}

/*
 * Function:  OpenCats
 * ----------------------
 *  Open the system catalogs and place their entries into the catalog caches. Initialize the buffer
 *  pool control fields.
 *  
 *  returns: OK upon successful execution
 *           NOTOK otherwise
 */

int OpenCats()
{
    //printf("OpenCats \n ");

    char cat_info[8];
    int i,j;
    int num_recs_relcat;
    int num_pages_relcat;
    char full_rel_path[ 3*RELNAME ];
    FILE *fp;
   
    /* Initializing Buffer pool control fields.*/
    g_cache_in_use[0] = g_cache_in_use[1] = TRUE;
    for(i=2; i<MAXOPEN; i++)
        g_cache_in_use[i] = FALSE;

    for(i=0; i<MAXOPEN; i++){
        g_cache_timestamp[i] = 0;
        g_cache_dirty[i] = FALSE;
    }

    /* Creating cache[0] entry for relcat */
    sprintf(full_rel_path,"%s/%s/%s",PATH,g_db_name,"relcat");
    fp = fopen(full_rel_path,"rb");
    fseek(fp,PAGESIZE - MAXRECORD + 32,SEEK_SET);
    fread(cat_info,1,8,fp);
    fclose(fp);
    num_recs_relcat  = readIntFromByteArray(cat_info, 0);
    num_pages_relcat = readIntFromByteArray(cat_info, 4);

    g_catcache[0].relName   = "relcat";
    g_catcache[0].recLength = 40;
    g_catcache[0].recsPerPg = 12;
    g_catcache[0].numAttrs  = 6;
    g_catcache[0].numRecs   = num_recs_relcat;
    g_catcache[0].numPgs    = num_pages_relcat;
    g_catcache[0].relcatRid = { 1, 1};
    g_catcache[0].relFile   = open(full_rel_path,O_RDWR);
    g_catcache[0].dirty     = FALSE;
    g_catcache[0].attrList  = create_attr_cat_relcat();
    
    //And Add them in the correct loc and make cache[0] entry.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 
}