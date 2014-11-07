#include "../include/defs.h"
#include "../include/error.h"
#include "../include/globals.h"
#include "../include/helpers.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Creates a new relation with the specified name and attributes.
 * offset -- offset of attribute within record
 * length -- length of attribute
 * type -- attribute type: ``i'', ``f'', or ``s''
 * attrName -- name of attribute
 * relName -- name of relation
 * @param argc
 * @param argv
 * @return
 */
//TODO Should attribute and relation names be case sensitive
int Create(int argc, char **argv) {
    /*     print command line arguments
     short k;  iteration counter
     printf("%s:\n", argv[0]);
     for (k = 1; k < argc; ++k)
     printf("\targv[%d] = %s\n", k, argv[k]);
     printf("Create \n");*/

    int offset, length, i;
    char type, attrName[RELNAME], relName[RELNAME];
    strcpy(relName, *argv[1]);

    if (isValidString(relName) == NOTOK) {
        return ErrorMsgs(INVALID_ATTR_NAME, g_print_flag);
    }
    if (isRelationExists(relName) == OK) {
        return ErrorMsgs(REL_ALREADY_EXISTS, g_print_flag);
    }

    /* Creating attribute catalog records */
    int numAttrs;

    for (i = 2, numAttrs = 0, offset = 0; i < argc; i = i + 2, numAttrs++) {
        //TODO INSERT
    }


    return OK; /* all's fine */
}

int getN(char *sN) {
    int i, N;
    N = atoi(sN + 1);
    return N;
}

int isRelationExists(char *relName) {
    struct attrCatalog *attrList = g_catcache[ATTRCAT_CACHE].attrList;
    while (attrList != NULL) {
        if (strcmp(attrList->attrName, "relName")) {
            break;
        }
        attrList = attrList->next;
    }
    int offset = attrList->offset;
    Rid startRid = { 0, 0 };
    Rid *foundRid;
    char *recPtr = (char *) malloc(attrList->length);
    if (FindRec(ATTRCAT_CACHE, startRid, &foundRid, recPtr, STRING, attrList->length, offset,
            relName, EQ) == OK) {
        return OK;
    } else {
        return NOTOK;
    }
}

int isValidString(char *string) {
    if (!isalpha(string[0])) {
        return NOTOK;
    } else if (strlen(string) >= RELNAME) {
        return NOTOK;
    } else {
        return OK;
    }
}

int getSizeOfAttr(char *attrFormat) {
    int size = 0;
    switch (attrFormat[0]) {
        case INTEGER:
            size = sizeof(int);
            break;
        case STRING:
            size = getN(attrFormat);
            break;
        case FLOAT:
            size = sizeof(float);
            break;
        default:
            break;
    }
    return size;
}
