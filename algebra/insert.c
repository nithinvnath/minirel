#include "../include/defs.h"
#include "../include/error.h"
#include "../include/globals.h"
#include "../include/helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct attrCatalog* getAttrCatalog(struct attrCatalog *attrList, char *attrName) {
    struct attrCatalog *list = attrList;
    while (list != NULL) {
        if (strcmp(attrName, list->attrName) == 0) {
            break;
        }
        list = list->next;
    }
    return list;
}

void removeQuotes(char *quotedString) {
    /* Values are passed as quoted string. We store it in memory after removing the quotes */
    int length = strlen(quotedString);
    strncpy(quotedString, quotedString + 1, length - 1);
}

//TODO Should we throw error in case not all attributes are given?
/**
 * Implementation of insert command.
 * argv[0] - insert
 * argv[1] - relation name
 * argv[2] - attr name 1
 * argv[3] - attr value 1
 * ...
 * argv[argc] - NIL
 *
 * @param argc
 * @param argv
 * @return OK if success
 */
int Insert(int argc, char **argv) {
    /* print command line arguments
     short k;  iteration counter
     printf("%s:\n", argv[0]);
     for (k = 1; k < argc; ++k)
     printf("\targv[%d] = %s\n", k, argv[k]);

     printf("Insert \n");*/

    if ((strcmp(argv[0], "insert") == 0)
            && (strcmp(argv[1], RELCAT) == 0 || strcmp(argv[1], ATTRCAT) == 0)) {
        return ErrorMsgs(METADATA_SECURITY, g_print_flag);
    }

    char relName[RELNAME], attrName[RELNAME];
    strcpy(relName, argv[2]);

    int relNum = OpenRel(relName);
    if (relNum == NOTOK) {
        return NOTOK;
    }

    int i;
    /* Using calloc so that memory is initialized to zero.
     This is required while checking for duplicates in the relation */
    char *recPtr = (char *) calloc(g_catcache[relNum].recLength, sizeof(char));
    struct attrCatalog *attr = NULL;
    for (i = 2; i < argc; i += 2) {
        attr = getAttrCatalog(g_catcache[relNum].attrList, argv[i]);
        if (attr == NULL) {
            return ErrorMsgs(ATTR_NOT_IN_REL, g_print_flag);
        }
        removeQuotes(argv[i + 1]);
        strncpy(recPtr + attr->offset, argv[i + 1], attr->length);
    }

    /* Now checking for duplicates */
    Rid *foundRid, startRid = { 0, 0 };
    char *record;
    while (GetNextRec(relNum, &startRid, &foundRid, &record) == OK) {
        if (compareRecords(record, recPtr, attr->length) == OK) {
            return ErrorMsgs(DUPLICATE_TUPLE, g_print_flag);
        }
    }

    return InsertRec(relNum, recPtr);
}

