/*
 * select.c
 *
 *  Created on: 7-Oct-2014
 *      Author: Dheeraj
 */

#include "../include/select.h"

/*
 * Function:  Select() 
 * ------------------------
 * implements relational selection command
 *
 * argv[0] = “select”
 * argv[1] = result relation
 * argv[2] = source relation
 * argv[3] = attribute name
 * argv[4] = operator
 * argv[5] = value
 * argv[argc] = NIL
 *  
 * returns: OK upon successfully performed selection
 *           NOTOK: otherwise
 *
 * GLOBAL VARIABLES MODIFIED:
 *     <None>
 *
 * ERRORS REPORTED:
 *     ARGC_INSUFFICIENT
 *     RELNOEXIST
 *     ATTRNOEXIST
 *
 * ALGORITHM:
 *   1. Checks for Errors.
 *   2. Opens Source Relation and target relation
 *   3. Finds records satisfying given condition using FindRec
 *   4. Inserts into target relation, if such record is found
 *   5. Repeats 3-4 till last matching record of source relation.
 *
 * IMPLEMENTATION NOTES:
 *     Uses OpenRel, FindRelNum, FindRec, InsertRec from physical layer
 *     Uses Create from schema layer.
 *
 */

int Select(int argc, char **argv) {
    if (g_DBOpenFlag != OK) {
        return ErrorMsgs(DB_NOT_OPEN, g_PrintFlag);
    }
    int relNum, newRelNum, numAttrs, count, i, retVal, offset, attrFoundFlag = 0;
    int attrSize, intVal;
    float floatVal;
    struct attrCatalog* head;
    datatype type;
    Rid startRid = { 1, 0 }, *foundRid;
    char **createArgumentList, *recPtr;

    if (argc < 6)
        return ErrorMsgs(ARGC_INSUFFICIENT, g_PrintFlag);

    if (OpenRel(argv[2]) == NOTOK)
        return ErrorMsgs(RELNOEXIST, g_PrintFlag);
    /* Finding the relNum of Source Relation */
    relNum = FindRelNum(argv[2]);

    head = g_CatCache[relNum].attrList;
    numAttrs = g_CatCache[relNum].numAttrs;

    /* Preparing Argument list which should be passed to Create() */
    createArgumentList = malloc(sizeof(char*) * (numAttrs + 1) * 2);
    createArgumentList[0] = malloc(sizeof(char) * RELNAME);
    createArgumentList[1] = malloc(sizeof(char) * RELNAME);

    for (count = 2; count < (numAttrs + 1) * 2; count++) {
        createArgumentList[count] = malloc(sizeof(char) * RELNAME);
        createArgumentList[count + 1] = malloc(sizeof(char) * 4);
    }

    strcpy(createArgumentList[0], "create");
    strcpy(createArgumentList[1], argv[1]);
    count = 2;
    while (head != NULL) {
        strcpy(createArgumentList[count], head->attrName);
        switch (head->type) {
            case INTEGER:
                strcpy(createArgumentList[count + 1], "i");
                break;
            case STRING:
                sprintf(createArgumentList[count + 1], "s%d", head->length);
                break;
            case FLOAT:
                strcpy(createArgumentList[count + 1], "f");
                break;
        }
        /* This is to catch the desired attribute's specifications from Source relation. 
         Expected to happen only once in this loop */
        if (strcmp(head->attrName, argv[3]) == 0) {
            attrFoundFlag = 1;
            offset = head->offset;
            type = head->type;
            attrSize = head->length;
        }
        head = head->next;
        count = count + 2;
    }
    /* Given attribute name never appeared in attr linkedlist */
    if (attrFoundFlag == 0)
        ErrorMsgs(ATTRNOEXIST, g_PrintFlag);

    retVal = Create((numAttrs + 1) * 2, createArgumentList);

    for (i = 0; i < (numAttrs + 1) * 2; i++)
        free(createArgumentList[i]);
    free(createArgumentList);

    if (retVal == NOTOK)
        return NOTOK;

    OpenRel(argv[1]);
    newRelNum = FindRelNum(argv[1]);

    switch (type) {
        case STRING:
            break;
        case INTEGER:
            intVal = atoi(argv[5]);
            convertIntToByteArray(intVal, argv[5]);
            break;
        case FLOAT:
            floatVal = atof(argv[5]);
            convertFloatToByteArray(floatVal, argv[5]);
            break;
    }
    /* Finding record from Source, which satisfying given condition, and Adding to Result Relation*/
    while (FindRec(relNum, &startRid, &foundRid, &recPtr, type, attrSize, offset, argv[5],
            readIntFromByteArray(argv[4], 0)) == OK) {
        InsertRec(newRelNum, recPtr);
        startRid = (*foundRid);
        free(foundRid);
    }
    return OK;
}
