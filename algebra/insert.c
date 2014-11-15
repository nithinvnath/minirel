#include "../include/insert.h"

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
/*    int k;
    for(k=0; k<argc; k++)
        printf("%s\n",argv[k]);
    printf("\n");

*/    if ((strcmp(argv[0], "_insert") != 0)
            && (strcmp(argv[1], RELCAT) == 0 || strcmp(argv[1], ATTRCAT) == 0)) {
        return ErrorMsgs(METADATA_SECURITY, g_print_flag);
    }

    char relName[RELNAME], attrName[RELNAME];
    strcpy(relName, argv[1]);

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

        char *nptr, *endptr;
        int intval;
        float floatval;
        switch (attr->type) {
            case INTEGER:
                intval = strtol(argv[i + 1], &nptr, 10);
                endptr = argv[i + 1] + (int)(strlen(argv[i + 1]));
                if (nptr != endptr) {
                    return ErrorMsgs(INTEGER_EXPECTED, g_print_flag);
                }
                convertIntToByteArray(intval, recPtr + attr->offset);
                break;
            case FLOAT:
                floatval = strtof(argv[i + 1], &nptr);
                endptr = argv[i + 1] + (strlen(argv[i + 1] - 1));
                if (nptr != endptr) {
                    return ErrorMsgs(FLOAT_EXPECTED, g_print_flag);
                }
                convertFloatToByteArray(floatval, recPtr + attr->offset);
                break;
            case STRING:
                removeQuotes(argv[i + 1]);
                strncpy(recPtr + attr->offset, argv[i + 1], attr->length);
                break;
            default:
                break;
        }
    }

    //Duplicate checking done in InsertRec
    return InsertRec(relNum, recPtr);
}

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
    /* In strncpy src and dest should not overlap */
    int length;
    length = strlen(quotedString);
    char *tempString = malloc(sizeof(char)*length);
    strcpy(tempString,quotedString);
    strncpy(quotedString, tempString + 1 , length - 2);
    free(tempString);
}
