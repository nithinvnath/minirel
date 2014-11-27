/*
 * join.c
 *
 *  Created on: 7-Oct-2014
 *      Author: Dheeraj
 */

#include "../include/join.h"

/*
 * Function:  Join() 
 * ------------------------
 * implements natural join
 *
 * argv[0] = “join”
 * argv[1] = result relation
 * argv[2] = source relation 1
 * argv[3] = attribute name 1
 * argv[4] = source relation 2
 * argv[5] = attribute name 2
 * argv[argc] = NIL
 *  
 *  returns: OK upon successfully performed join relation
 *           NOTOK: otherwise
 *
 *  GLOBAL VARIABLES MODIFIED:
 *      <None> 
 *
 *  ERRORS REPORTED:
 *      ARGC_INSUFFICIENT
 *      RELNOEXIST
 *      ATTRNOEXIST
 *      TYPE_MISMATCH
 *
 *  ALGORITHM:
 *   1. Check for Errors
 *   2. Opens both relations and finds offsets of join attributes from both relations.
 *   3. Rename the attributes in 2nd relation if names are matched from first relation (if any)
 *   4. Creates a new relation with combined attribute set from source relations, 
 *      without repeating join attribute.
 *   5. Finds records of relation1 using GetNextRec()
 *   6. Searches in relation2 for matching record using FindRec()
 *   7. Repeats 5-6 till last record of relation1, and inserts into new relation.
 *
 *  IMPLEMENTATION NOTES:
 *      Uses OpenRel, FindRelNum, GetNextRec, FindRec, InsertRec from physical layer.
 *      Uses Create from schema layer
 *
 *
 */

int Join(int argc, char **argv) {
    if (g_DBOpenFlag != OK) {
        return ErrorMsgs(DB_NOT_OPEN, g_PrintFlag);
    }
    int relNum1, relNum2, count, attrFoundFlag = 0, i, retVal, recResultLength;
    int numAttrsRel1, numAttrsRel2, numAttrsTotal;
    int offset1, offset2, attrSize1, attrSize2, newRelNum;
    datatype type1, type2;
    struct attrCatalog *head;
    char **argumentList, *recPtr1, *recPtr2, *recResult;
    Rid startRidRel1 = { 1, 0 }, startRidRel2 = { 1, 0 }, *foundRidRel1, *foundRidRel2;

    if (argc < 6)
        return ErrorMsgs(ARGC_INSUFFICIENT, g_PrintFlag);

    if ((relNum1 = OpenRel(argv[2])) == NOTOK || (relNum2 = OpenRel(argv[4])) == NOTOK)
        return ErrorMsgs(RELNOEXIST, g_PrintFlag);

    numAttrsRel1 = g_CatCache[relNum1].numAttrs;
    numAttrsRel2 = g_CatCache[relNum2].numAttrs;
    numAttrsTotal = numAttrsRel1 + numAttrsRel2;

    /* Preparing Argument list which should be passed to Create() */
    argumentList = malloc(sizeof(char*) * (numAttrsTotal * 2));
    argumentList[0] = malloc(sizeof(char) * RELNAME);
    argumentList[1] = malloc(sizeof(char) * RELNAME);

    for (count = 2; count < numAttrsTotal * 2; count++) {
        argumentList[count] = malloc(sizeof(char) * RELNAME);
        argumentList[count + 1] = malloc(sizeof(char) * 4);
    }

    strcpy(argumentList[0], "create");
    strcpy(argumentList[1], argv[1]);

    count = 2;
    head = g_CatCache[relNum1].attrList;

    while (head != NULL) {
        strcpy(argumentList[count], head->attrName);
        switch (head->type) {
            case INTEGER:
                strcpy(argumentList[count + 1], "i");
                break;
            case STRING:
                sprintf(argumentList[count + 1], "s%d", head->length);
                break;
            case FLOAT:
                strcpy(argumentList[count + 1], "f");
                break;
        }
        if (strcmp(head->attrName, argv[3]) == 0) {
            attrFoundFlag = 1;
            offset1 = head->offset;
            type1 = head->type;
            attrSize1 = head->length;
        }
        head = head->next;
        count = count + 2;
    }
    if (attrFoundFlag == 0)
        return ErrorMsgs(ATTRNOEXIST, g_PrintFlag);

    /* Next Relation's attribute list */
    attrFoundFlag = 0;
    head = g_CatCache[relNum2].attrList;

    while (head != NULL) {
        if (strcmp(head->attrName, argv[5]) == 0) {
            attrFoundFlag = 1;
            offset2 = head->offset;
            type2 = head->type;
            attrSize2 = head->length;
        }
        /* Skipping the join attribute in 2nd relation */
        if (strcmp(head->attrName, argv[5]) == 0) {
            head = head->next;
            continue;
        }
        strcpy(argumentList[count], head->attrName);
        /* This is to give different name for same attribute names in two Relations */
        for (i = 2; i < numAttrsRel1 + 2; i = i + 2)
            if (strcmp(argumentList[i], head->attrName) == 0) {
                strcat(argumentList[count], "_2");
            }

        switch (head->type) {
            case INTEGER:
                strcpy(argumentList[count + 1], "i");
                break;
            case STRING:
                sprintf(argumentList[count + 1], "s%d", head->length);
                break;
            case FLOAT:
                strcpy(argumentList[count + 1], "f");
                break;
        }
        head = head->next;
        count = count + 2;
    }
    if (attrFoundFlag == 0)
        return ErrorMsgs(ATTRNOEXIST, g_PrintFlag);

    retVal = Create(numAttrsTotal * 2, argumentList);
    if (retVal == NOTOK)
        return NOTOK;

    OpenRel(argv[1]);
    newRelNum = FindRelNum(argv[1]);

    for (i = 0; i < numAttrsTotal * 2; i++)
        free(argumentList[i]);
    free(argumentList);

    if (type1 != type2)
        return ErrorMsgs(TYPE_MISMATCH, g_PrintFlag);

    recResultLength = g_CatCache[relNum1].recLength + g_CatCache[relNum2].recLength - attrSize2;
    recResult = malloc(sizeof(char) * (recResultLength));

    while (GetNextRec(relNum1, &startRidRel1, &foundRidRel1, &recPtr1) == OK) {
        startRidRel2.pid = 1;
        startRidRel2.slotnum = 0;

        while (FindRec(relNum2, &startRidRel2, &foundRidRel2, &recPtr2, type2, attrSize2, offset2,
                recPtr1 + offset1, EQ) == OK) {

            copyBinaryArray(recResult, recPtr1, g_CatCache[relNum1].recLength);
            copyBinaryArray(recResult + g_CatCache[relNum1].recLength, recPtr2, offset2);
            copyBinaryArray(recResult + g_CatCache[relNum1].recLength + offset2,
                    recPtr2 + offset2 + attrSize2,
                    g_CatCache[relNum2].recLength - offset2 - attrSize2);

            InsertRec(newRelNum, recResult);

            startRidRel2 = *foundRidRel2;
            free(foundRidRel2);
        }
        startRidRel1 = *foundRidRel1;
        free(foundRidRel1);
    }

    return OK;
}

/*
 * Function:  copyBinaryArray()
 * ------------------------------
 * copies binary array from source to destination.
 *
 * dest : destination array
 * source: source array
 * length: length of the array
 */

void copyBinaryArray(char *dest, char *source, int length) {
    int i;
    for (i = 0; i < length; ++i) {
        dest[i] = source[i];
    }
}
