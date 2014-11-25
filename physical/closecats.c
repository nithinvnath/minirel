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

int CloseCats() {
    int i;

    if (g_CacheInUse[0] == FALSE || g_CacheInUse[1] == FALSE)
        return NOTOK;

    for (i = 2; i < MAXOPEN; i++)
        if (g_CacheInUse[i] == TRUE)
            CloseRel(i);
    /* Closing Relation attrcat */
    CloseRel(ATTRCAT_CACHE);
    /* Closing Relation relcat */
    CloseRel(RELCAT_CACHE);

    return OK;
}
