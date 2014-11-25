/*
 * delete.c
 *
 *  Created on: 7-Oct-2014
 *      Author: Dheeraj
 */

#include "../include/delete.h"

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

int Delete(int argc, char **argv) {
    if (g_db_open_flag != OK) {
        return ErrorMsgs(DB_NOT_OPEN, g_print_flag);
    }
    int relNum, numAttrs, i, offset, attr_found_flag = 0;
    int attrSize, int_val;
    float float_val;
    struct attrCatalog* head;
    datatype type;
    Rid startRid = { 1, 0 }, *foundRid;

    char *recPtr;

    if (argc < 5)
        return ErrorMsgs(ARGC_INSUFFICIENT, g_print_flag);

    if ((strcmp(argv[0], "_delete") != 0)
            && (strcmp(argv[1], RELCAT) == 0 || strcmp(argv[1], ATTRCAT) == 0)) {
        return ErrorMsgs(METADATA_SECURITY, g_print_flag);
    }

    if (OpenRel(argv[1]) == NOTOK)
        return ErrorMsgs(RELNOEXIST, g_print_flag);
    /* Finding the relNum of Relation */
    relNum = FindRelNum(argv[1]);

    head = g_catcache[relNum].attrList;
    numAttrs = g_catcache[relNum].numAttrs;

    while (head != NULL) {
        /* This is to catch the desired attribute's specifications from Source relation. 
         Expected to happen only once in this loop */
        if (strcmp(head->attrName, argv[2]) == 0) {
            attr_found_flag = 1;
            offset = head->offset;
            type = head->type;
            attrSize = head->length;
        }
        head = head->next;
    }
    /* Given attribute name never appeared in attr linkedlist */
    if (attr_found_flag == 0)
        ErrorMsgs(ATTRNOEXIST, g_print_flag);

    switch (type) {
        case INTEGER:
            int_val = atoi(argv[4]);
            convertIntToByteArray(int_val, argv[4]);
            break;
        case FLOAT:
            float_val = atof(argv[4]);
            convertFloatToByteArray(float_val, argv[4]);
            break;
    }
    /* Finding record from Relation and deleting corresponding Rid Entry */
    while (FindRec(relNum, &startRid, &foundRid, &recPtr, type, attrSize, offset, argv[4],
            readIntFromByteArray(argv[3],0)) == OK) {
        DeleteRec(relNum, foundRid);
        startRid = (*foundRid);
        free(foundRid);
    }
    return OK;
}
