/*
 * openrel.c
 *
 *  Created on: 28-Oct-2014
 *      Author: Dheeraj
 */

#include "../include/cache.h"
#include "../include/globals.h"
#include "../include/readpage.h"
#include "../include/error.h"
#include "../include/helpers.h"
#include "../include/defs.h"
#include "../include/findrec.h" 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

//FIXME line 81, code after updaterec implementation
/*
 * Function:  OpenRel 
 * ----------------------
 * Open relation 'relName' and return its relation number.
 *
 *  RelName: name of the relation
 *  
 *  returns: RelNum
 *           error code otherwise
 */

int OpenRel(char* RelName)
{

    Rid start, *found;
    char* bin_data;
    char full_rel_path[ 3*RELNAME ];
    struct attrCatalog *temp=NULL, *newnode=NULL;
    bool first_exec = TRUE;
    int i,j;

    start.pid = 1;
    start.slotnum = 0;

    FindRec(0, &start, found, bin_data, 's', RELNAME, 0, RelName, EQ);

    if(found == NULL){
        return RELNOEXIST;
    }/* Relation does not exist with given Relation Name */
    else{
        /* -------Cache Management----------- 
        take out first cache position which is empty ( or choose one to replace )
        fill out entries and return RelNum */

        for (i=2; i<MAXOPEN; i++){
            if (g_cache_in_use[i] == FALSE)
                break;
        }

        if (i != MAXOPEN ){
            g_cache_in_use[i] = TRUE;
            g_cache_timestamp[i] = 1;
            g_cache_dirty[i] = FALSE;

            for (j=2; j<MAXOPEN; j++){
                if(g_cache_in_use[j] == TRUE)
                    g_cache_timestamp[j]++;
            }
        }/* Found an empty slot.*/
        else{
            for (i=2; i<MAXOPEN; i++){
                if(g_cache_timestamp[i] == 18)
                    break;
            }

            g_cache_timestamp[i] = 1;
            for (j = 2; j < MAXOPEN; ++j){
                g_cache_timestamp[j]++;
            }

            if(g_catcache[i].dirty == TRUE ){
                /*update numRecs, numPgs in RelCat relation, from g_catcache[i] entry*/ 
            }
        }/* Replaced an existing cat_cahe enty*/

        /* position i is available */
        strcpy(g_catcache[i].relName, RelName);
        g_catcache[i].recLength = readIntFromByteArray(bin_data, 20);
        g_catcache[i].recsPerPg = readIntFromByteArray(bin_data, 24);
        g_catcache[i].numAttrs  = readIntFromByteArray(bin_data, 28);
        g_catcache[i].numRecs   = readIntFromByteArray(bin_data, 32);
        g_catcache[i].numPgs    = readIntFromByteArray(bin_data, 36);

        g_catcache[i].relcatRid = *found;
        g_catcache[i].dirty = FALSE;

        sprintf(full_rel_path,"%s/%s/%s",PATH,g_db_name,RelName);
        g_catcache[i].relFile = open(full_rel_path,O_RDWR);

        FindRec(1, &start, found, bin_data, 's', RELNAME, 32, RelName, EQ);

        if(found == NULL){
            return NO_ATTRS_FOUND;
        }

        while(found!=NULL){
            newnode = malloc(sizeof(struct attrCatalog));

            if(first_exec == TRUE){
                g_catcache[i].attrList = newnode; 
                temp = newnode;
                first_exec = FALSE;
            }
            else{
                temp->next = newnode;
                temp = newnode;
            }

            temp->offset = readIntFromByteArray(bin_data, 0);
            temp->length = readIntFromByteArray(bin_data, 4);
            temp->type   = readIntFromByteArray(bin_data, 8);
            readStringFromByteArray(temp->attrName, bin_data, 12, RELNAME);
            readStringFromByteArray(temp->relName, bin_data, 32, RELNAME);

            start = *found;
            free(found);
            FindRec(1, &start, found, bin_data, 's', RELNAME, 32, RelName, EQ);
        }
    return i;
    }
}