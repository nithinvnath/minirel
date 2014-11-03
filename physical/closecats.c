/*
 * closecats.c
 *
 *  Created on: 1-Nov-2014
 *      Author: Dheeraj
 */

#include "../include/closecats.h"

/*
 * Function: CloseCat() 
 * ----------------------
 * Closes catalog files
 *
 *  returns: OK on success
 *           NOTOK on failure
 */

int CloseCats()
{
    int i;

    if (g_cache_in_use[0] == FALSE || g_cache_in_use[1] == FALSE)
        return NOTOK;

    for(i=2; i<MAXOPEN; i++)
        if(g_cache_in_use[i] == TRUE)
            CloseRel(i);
    /* Closing Relation attrcat */
    CloseRel(1);
    /* Closing Relation relcat */
    CloseRel(0); 

    return OK;
}
