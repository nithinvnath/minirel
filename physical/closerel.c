/*
 * closerel.c
 *
 *  Created on: 31-Oct-2014
 *      Author: Dheeraj
 */

#include "../include/closerel.h"

/*
 * Function: CloseRel() 
 * ----------------------
 * Close the relation identified by relNum after writing to disk any changes in its buffer page or 
 * in its cached catalog information
 *
 *  relNum : relation number
 *
 *  returns: OK on success
 *           NOTOK on failure
 */

int CloseRel(int relNum)
{
    int numPgs, numRecs;
    char *recPtr;
    Rid startRid = {1,0}, *foundRid;

    FlushPage(relNum);

    if(g_catcache[relNum].dirty == FALSE)
        return OK;
    else{
        if( FindRec(0, &startRid, foundRid, recPtr, STRING, RELNAME, 0, g_catcache[relNum].relName, EQ) == NOTOK ){
            ErrorMsgs(RELNOEXIST);
            return NOTOK;   
        }
        else{
            numPgs  = g_catcache[relNum].numPgs;
            numRecs = g_catcache[relNum].numRecs;
            convertIntToByteArray(numRecs,recPtr + 32);
            convertIntToByteArray(numPgs,recPtr + 36);
            FlushPage(0);

            struct attrCatalog *temp, *linked_list_head = g_catcache[relNum].attrList;
            g_catcache[relNum].dirty = FALSE;
            g_cache_in_use[relNum] = FALSE;
            g_cache_timestamp[relNum] = 0;
            close(g_catcache[relNum].relFile);

            temp = linked_list_head;
            while(temp != NULL){
                linked_list_head = temp -> next;
                free(temp);
                temp = linked_list_head;
            }
        }
    }
    return OK;
}
