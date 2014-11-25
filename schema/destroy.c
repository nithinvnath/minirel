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
 *
 *
 * GLOBAL VARIABLES MODIFIED:
 *      g_CacheInUse[relNum] = FALSE // Freeing cache slot of destroying relation
 *       
 * ERRORS REPORTED:
 *      ARGC_INSUFFICIENT
 *      DB_NOT_OPEN
 *      METADATA_SECURITY
 *      RELNOEXIST
 *
 * ALGORITHM:
 *   1. checks for relation existance and metadata security
 *   2. Removes the file represents the relation.
 *   3. Deletes entries of given relName from attrcat and relcat.
 *
 * IMPLEMENTATION NOTES:
 *      Uses FindRelNum from physical layer
 *      Uses delete from algebra layer
 *
 */

int Destroy(int argc, char **argv) {
    if (g_DBOpenFlag != OK) {
        return ErrorMsgs(DB_NOT_OPEN, g_PrintFlag);
    }
    int pass_argc, i, relNum;
    char **pass_argv;

    if (argc < 2)
        return ErrorMsgs(ARGC_INSUFFICIENT, g_PrintFlag);

    if ((strcmp(argv[0], "_destroy") != 0)
            && (strcmp(argv[1], RELCAT) == 0 || strcmp(argv[1], ATTRCAT) == 0)) {
        return ErrorMsgs(METADATA_SECURITY, g_PrintFlag);
    }

    if (remove(argv[1]) != 0) {
        return ErrorMsgs(RELNOEXIST, g_PrintFlag);
    } /* File deletion failed*/

    pass_argc = 5;
    pass_argv = malloc(sizeof(char*) * 5);

    for (i = 0; i < 5; i++)
        pass_argv[i] = malloc(sizeof(char) * RELNAME);

    /* _delete is passed for bypassing metadata security */
    strcpy(pass_argv[0], "_delete");
    strcpy(pass_argv[1], ATTRCAT);
    strcpy(pass_argv[2], "relName");
    convertIntToByteArray(EQ,pass_argv[3]);
    strcpy(pass_argv[4], argv[1]);

    Delete(pass_argc, pass_argv);

    strcpy(pass_argv[1], RELCAT);

    Delete(pass_argc, pass_argv);

    relNum = FindRelNum(argv[1]);
    g_CacheInUse[relNum] = FALSE;

    for (i = 0; i < 5; ++i) {
        free(pass_argv[i]);
    }
    free(pass_argv);

    return OK;
}
