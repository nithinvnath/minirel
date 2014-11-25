#include "../include/insert.h"

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

    if ((strcmp(argv[0], "_insert") != 0)
            && (strcmp(argv[1], RELCAT) == 0 || strcmp(argv[1], ATTRCAT) == 0)) {
        return ErrorMsgs(METADATA_SECURITY, g_PrintFlag);
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
    char *recPtr = (char *) calloc(g_CatCache[relNum].recLength, sizeof(char));
    struct attrCatalog *attr = NULL;
    for (i = 2; i < argc; i += 2) {
        attr = getAttrCatalog(g_CatCache[relNum].attrList, argv[i]);
        if (attr == NULL) {
            return ErrorMsgs(ATTR_NOT_IN_REL, g_PrintFlag);
        }

        char *nptr, *endptr;
        int intval;
        float floatval;
        switch (attr->type) {
            case INTEGER:
                intval = strtol(argv[i + 1], &nptr, 10);
                convertIntToByteArray(intval, recPtr + attr->offset);
                break;
            case FLOAT:
                floatval = strtof(argv[i + 1], &nptr);
                endptr = argv[i + 1] + (strlen(argv[i + 1] - 1));
                convertFloatToByteArray(floatval, recPtr + attr->offset);
                break;
            case STRING:
                strncpy(recPtr + attr->offset, argv[i + 1], attr->length - 1);
                break;
            default:
                break;
        }
    }

    //Duplicate checking done in InsertRec
    return InsertRec(relNum, recPtr);
}
