/*
 * opencats.c
 *
 *  Created on: 30-Oct-2014
 *      Author: Dheeraj
 */

#include "../include/opencats.h"

/*
 * Function:  create_attr_cat_attrcat()
 * ------------------------------------
 *  create linkedlist form of attr_cat of attrcat relation
 *  
 *  returns: pointer to the head of linkedlist
 */

struct attrCatalog* create_attr_cat_attrcat()
{
    struct attrCatalog *temp, *newnode; 

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 32;
    (*newnode).length = 20;
    (*newnode).type   = STRING;
    strcpy( (*newnode).attrName, "relName");
    strcpy( (*newnode).relName,  "attrcat");
    (*newnode).next = NULL;
    temp = newnode;

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 12;
    (*newnode).length = 20;
    (*newnode).type   = STRING;
    strcpy( (*newnode).attrName, "attrName");
    strcpy( (*newnode).relName,  "attrcat");
    (*newnode).next = temp;
    temp = newnode;

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 8;
    (*newnode).length = 4;
    (*newnode).type   = INTEGER;
    strcpy( (*newnode).attrName, "type");
    strcpy( (*newnode).relName,  "attrcat");
    (*newnode).next = temp;
    temp = newnode;

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 4;
    (*newnode).length = 4;
    (*newnode).type   = INTEGER;
    strcpy( (*newnode).attrName, "length");
    strcpy( (*newnode).relName,  "attrcat");
    (*newnode).next = temp;
    temp = newnode;

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 0;
    (*newnode).length = 4;
    (*newnode).type   = INTEGER;
    strcpy( (*newnode).attrName, "offset");
    strcpy( (*newnode).relName,  "attrcat");
    (*newnode).next = temp;
    temp = newnode;

    return temp;
}

/*
 * Function:  create_attr_cat_relcat
 * ----------------------------------
 *  create linkedlist form of attr_cat of relcat relation
 *  
 *  returns: pointer to the head of linkedlist
 */

struct attrCatalog* create_attr_cat_relcat()
{
    struct attrCatalog *temp, *newnode; 

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 36;
    (*newnode).length = 4;
    (*newnode).type   = INTEGER;
    strcpy( (*newnode).attrName, "numPgs");
    strcpy( (*newnode).relName,  "relcat");
    (*newnode).next = NULL;
    temp = newnode;

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 32;
    (*newnode).length = 4;
    (*newnode).type   = INTEGER;
    strcpy( (*newnode).attrName, "numRecs");
    strcpy( (*newnode).relName,  "relcat");
    (*newnode).next = temp;
    temp = newnode;

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 28;
    (*newnode).length = 4;
    (*newnode).type   = INTEGER;
    strcpy( (*newnode).attrName, "numAttrs");
    strcpy( (*newnode).relName,  "relcat");
    (*newnode).next = NULL;
    temp = newnode;

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 24;
    (*newnode).length = 4;
    (*newnode).type   = INTEGER;
    strcpy( (*newnode).attrName, "recsPerPg");
    strcpy( (*newnode).relName,  "relcat");
    (*newnode).next = NULL;
    temp = newnode;

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 20;
    (*newnode).length = 4;
    (*newnode).type   = INTEGER;
    strcpy( (*newnode).attrName, "recLength");
    strcpy( (*newnode).relName,  "relcat");
    (*newnode).next = NULL;
    temp = newnode;

    newnode = malloc(sizeof(struct attrCatalog));
    (*newnode).offset = 0;
    (*newnode).length = 20;
    (*newnode).type   = STRING;
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
    char *recPtr;
    int i,j, ret_value;
    int num_recs_relcat;
    int num_pages_relcat;
    int num_recs_attrcat;
    int num_pages_attrcat;
    char full_rel_path[ 3*RELNAME ];

    Rid startRid = {1,0}, *foundRid;
 
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

    strcpy(g_catcache[0].relName, "relcat");
    g_catcache[0].recLength = 40;
    g_catcache[0].recsPerPg = 12;
    g_catcache[0].numAttrs  = 6;

    g_catcache[0].numRecs   = 2;
    g_catcache[0].numPgs    = 1;

    g_catcache[0].relcatRid.pid = 1;
    g_catcache[0].relcatRid.slotnum = 1;
    g_catcache[0].relFile   = open(full_rel_path,O_RDWR);
    g_catcache[0].dirty     = FALSE;
    g_catcache[0].attrList  = create_attr_cat_relcat();

    ret_value = FindRec(0, &startRid, &foundRid, &recPtr, STRING, RELNAME, 0, "relcat", EQ);
    if(ret_value == NOTOK){
        ErrorMsgs(NO_CATALOG_FOUND);
        return NOTOK;
    }

    num_recs_relcat  = readIntFromByteArray(recPtr, 32);
    num_pages_relcat = readIntFromByteArray(recPtr, 36);

    g_catcache[0].numRecs   = num_recs_relcat;
    g_catcache[0].numPgs    = num_pages_relcat;
    
    /* Creating cache[1] entry for attrcat */
    sprintf(full_rel_path,"%s/%s/%s",PATH,g_db_name,"attrcat");

    strcpy(g_catcache[1].relName, "attrcat");
    g_catcache[1].recLength = 52;
    g_catcache[1].recsPerPg = 9;
    g_catcache[1].numAttrs  = 5;

    g_catcache[1].numRecs   = 11;
    g_catcache[1].numPgs    = 2;

    g_catcache[1].relcatRid.pid = 1;
    g_catcache[1].relcatRid.slotnum = 2;
    g_catcache[1].relFile   = open(full_rel_path,O_RDWR);
    g_catcache[1].dirty     = FALSE;
    g_catcache[1].attrList  = create_attr_cat_attrcat();

    ret_value =FindRec(0, &startRid, &foundRid, &recPtr, STRING, RELNAME, 0, "attrcat", EQ);
    if(ret_value == NOTOK){
        ErrorMsgs(NO_CATALOG_FOUND);
        return NOTOK;
    }

    num_recs_relcat  = readIntFromByteArray(recPtr, 32);
    num_pages_relcat = readIntFromByteArray(recPtr, 36);

    g_catcache[1].numRecs   = num_recs_relcat;
    g_catcache[1].numPgs    = num_pages_relcat; 

    return OK;
}