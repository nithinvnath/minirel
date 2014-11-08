/*
 * findrelnum.c
 *
 *  Created on: 31-Oct-2014
 *      Author: Dheeraj
 */

#include "../include/findrelnum.h"

/*
 * Function: FindRelNum() 
 * ----------------------
 * Find the relation number of relation relName if it is currently open.
 *
 *  relName: Name of the relation to be found in the cache
 *
 *  returns: relnum on success
 *           NOTOK on failure
 */

int FindRelNum(char* relName)
{
    int i;
    bool found = FALSE;

    for(i=0; i<MAXOPEN; i++)
        if(g_cache_in_use[i] == TRUE && compareStrings(g_catcache[i].relName, relName, EQ) == TRUE){
            found = TRUE;
            break;
        }
    if(found == FALSE)
        return NOTOK;
    else
        return i;
}
