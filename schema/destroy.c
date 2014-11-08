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

int Destroy (int argc, char **argv)
{
    int pass_argc, i;
    char **pass_argv;

    if(argc < 2)
        return ErrorMsgs(ARGC_INSUFFICIENT,g_print_flag);

    if ((strcmp(argv[0], "_destroy") != 0)
            && (strcmp(argv[1], RELCAT) == 0 || strcmp(argv[1], ATTRCAT) == 0)) {
        return ErrorMsgs(METADATA_SECURITY, g_print_flag);
    }

    if(remove(argv[1]) != 0){
        return ErrorMsgs(RELNOEXIST,g_print_flag);
    } /* File deletion failed*/

    pass_argc = 5;
    pass_argv = malloc(sizeof(char*) * 5);

    for(i = 0; i < 5; i++)
        pass_argv[i] = malloc(sizeof(char) * RELNAME);

    /* _delete is passed for bypassing metadata security */
    strcpy(pass_argv[0], "_delete");
    strcpy(pass_argv[1], "attrcat");
    strcpy(pass_argv[2], "relName");
    sprintf(pass_argv[3], "%d",EQ);
    strcpy(pass_argv[4], argv[1]);

    Delete(pass_argc, pass_argv);

    strcpy(pass_argv[1], "relcat");
    strcpy(pass_argv[2], "relName");
    sprintf(pass_argv[3], "%d",EQ);
    strcpy(pass_argv[4], argv[1]);

    Delete(pass_argc, pass_argv);

    for (i = 0; i < 5; ++i){
        free(pass_argv[i]);
    }
    free(pass_argv);

    return OK;
}