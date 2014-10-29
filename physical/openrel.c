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

#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

//FIXME use the generic code for datatye conversion
//FIXME line 103, code after updaterec implementation

/*
 * Function:  bin_to_int
 * ----------------------
 * Converts binary data stored as char array (takes first 4 bytes) to integer
 *
 *  bin_data : char pointer at which binary data starts
 *  
 *  returns: converted integer
 */
int bin_to_int(char* bin_data)
{
    return bin_data[0] | bin_data[1]>>8 | bin_data[2]>>16 | bin_data[3]>>24 ;    
}

/*
 * Function:  bin_to_short
 * ----------------------
 * Converts binary data stored as char array (takes first 2 bytes) to short
 *
 *  bin_data : char pointer at which binary data starts
 *  
 *  returns: converted short
 */
short bin_to_short(char* bin_data)
{
    return bin_data[0] | bin_data[1]>>8;    
}
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
    char full_rel_path[ 3*NAME_MAX_LENGTH ];
    struct attrCatalog *temp=NULL, *newnode=NULL;
    bool first_exec = TRUE;
    int i,j;

    start.pid = 1;
    start.slotnum = 0;

    FindRec(0, &start, found, bin_data, 's', RELNAME, 0, RelName, 501);

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
        g_catcache[i].recLength = bin_to_short(bin_data + 20);
        g_catcache[i].recsPerPg = bin_to_short(bin_data + 22);
        g_catcache[i].numAttrs  = bin_to_short(bin_data + 24);
        g_catcache[i].numRecs   = bin_to_int(bin_data + 26);
        g_catcache[i].numPgs    = bin_to_int(bin_data + 30);

        g_catcache[i].relcatRid = *found;
        g_catcache[i].dirty = FALSE;

        sprintf(full_rel_path,"%s/%s/%s",PATH,g_db_name,RelName);
        g_catcache[i].relFile = open(full_rel_path,O_RDWR);

        FindRec(1, &start, found, bin_data, 's', RELNAME, 28, RelName, 501);

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

            temp->offset = bin_to_short(bin_data);
            temp->length = bin_to_short(bin_data + 2);
            temp->type   = bin_to_int(bin_data + 4);
            strncpy(temp->attrName,bin_data + 8, RELNAME);
            strncpy(temp->relName,RelName, RELNAME);

            start = *found;
            free(found);
            FindRec(1, &start, found, bin_data, 's', RELNAME, 28, RelName, 501);
        }
    return i;
    }
}