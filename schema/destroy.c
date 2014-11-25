/*
 * destroy.c
 *
 *  Created on: 9-Nov-2014
 *      Author: Dheeraj
 */

#include "../include/destroy.h"

/*
 * Function:  Destroy() 
 * ----------------------
 * Removes a relation from current database, and remove catalog entries as well
 *
 * argv[0] = “destroy”
 * argv[1] = relation name
 * argv[argc] = NIL
 *  
 *  returns: OK upon successful deletion of relation's file & catalog entries
 *           NOTOK otherwise
 */

#define DELETE_ARG_COUNT 5

int Destroy(int argc, char **argv) {
    if (g_DBOpenFlag != OK) {
        return ErrorMsgs(DB_NOT_OPEN, g_PrintFlag);
    }
    int i, relNum;
    char **deleteArgs;

    if (argc < 2)
        return ErrorMsgs(ARGC_INSUFFICIENT, g_PrintFlag);

    if ((strcmp(argv[0], "_destroy") != 0)
            && (strcmp(argv[1], RELCAT) == 0 || strcmp(argv[1], ATTRCAT) == 0)) {
        return ErrorMsgs(METADATA_SECURITY, g_PrintFlag);
    }

    if (remove(argv[1]) != 0) {
        return ErrorMsgs(RELNOEXIST, g_PrintFlag);
    } /* File deletion failed*/

    deleteArgs = malloc(sizeof(char*) * 5);

    for (i = 0; i < 5; i++)
        deleteArgs[i] = malloc(sizeof(char) * RELNAME);

    /* _delete is passed for bypassing metadata security */
    strcpy(deleteArgs[0], "_delete");
    strcpy(deleteArgs[1], ATTRCAT);
    strcpy(deleteArgs[2], "relName");
    convertIntToByteArray(EQ,deleteArgs[3]);
    strcpy(deleteArgs[4], argv[1]);

    Delete(DELETE_ARG_COUNT, deleteArgs);

    strcpy(deleteArgs[1], RELCAT);

    Delete(DELETE_ARG_COUNT, deleteArgs);

    relNum = FindRelNum(argv[1]);
    g_CacheInUse[relNum] = FALSE;

    for (i = 0; i < 5; ++i) {
        free(deleteArgs[i]);
    }
    free(deleteArgs);

    return OK;
}
