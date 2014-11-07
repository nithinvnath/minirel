/*
 * delete.c
 *
 *  Created on: 7-Oct-2014
 *      Author: Dheeraj
 */

#include "../include/defs.h"
#include "../include/error.h"
#include "../include/globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Function:  Delete() 
 * ------------------------
 * implements relational deletion command
 *
 * argv[0] = “delete”
 * argv[1] = source relation
 * argv[2] = attribute name
 * argv[3] = operator
 * argv[4] = value
 * argv[argc] = NIL
 *  
 *  returns: OK upon successfully performed deletion
 *           NOTOK: otherwise
 */

int Select (int argc, char **argv)
{
    int relNum, numAttrs, i, offset, attr_found_flag = 0;
    int attrSize;
    struct attrCatalog* head;
    datatype type;
    Rid startRid = {1,0}, *foundRid;

    char *recPtr;

    if(argc < 5)
        return ErrorMsgs(ARGC_INSUFFICIENT,g_print_flag);

    if(OpenRel(argv[2]) == NOTOK)
        return ErrorMsgs(RELNOESIST, g_print_flag);
    /* Finding the relNum of Relation */
    relNum = FindRelNum(argv[2]);

    head = g_catcache[relNum].attrList;
    numAttrs = g_catcache[relNum].numAttrs;

    while(head != NULL){
        /* This is to catch the desired attribute's specifications from Source relation. 
        Expected to happen only once in this loop */
        if(strcmp(head->attrName, argv[3]) == 0){
            attr_found_flag = 1;
            offset = head -> offset;
            type = head -> type;
            attrSize = head -> attrLength;
        }
        head = head->next;
    }
    /* Given attribute name never appeared in attr linkedlist */
    if(attr_found_flag == 0)
        ErrorMsgs(ATTRNOEXIST,g_print_flag);

    /* Finding record from Reltion and deleting corresponding Rid Entry */
    while( FindRec(relNum, &startRid, &foundRid, &recPtr, type, attrSize, 
                        offset, argv[5], atoi(argv[4])) == OK ){
        DeleteRec(relNum,foundRid);
        start = (*found);
        free(found);
    }
    return OK;
}