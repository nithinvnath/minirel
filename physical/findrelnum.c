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
 * GLOBAL VARIABLES MODIFIED:
 *      <None>
 *
 * ERRORS REPORTED:
 *      <None>
 *
 * ALGORITHM:
 *   1. Checks all cache entries and matches with given relName
 *   2. If there is a match with opened relation, return it's relNum.
 *   3. If not found, returns NOTOK.
 *
 * IMPLEMENTATION NOTES:
 *      <None>
 */

int FindRelNum(char* relName)
{
    int i;
    bool found = FALSE;

    for(i=0; i<MAXOPEN; i++)
        if(g_CacheInUse[i] == TRUE && compareStrings(g_CatCache[i].relName, relName, EQ) == TRUE){
            found = TRUE;
            break;
        }
    if(found == FALSE)
        return NOTOK;
    else
        return i;
}
