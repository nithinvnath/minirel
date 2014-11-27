#include "../include/insert.h"

/**
 * Implementation of insert command.
 * See documentation for complete specs
 *
 * argv[0] - insert
 * argv[1] - relation name
 * argv[2] - attr name 1
 * argv[3] - attr value 1
 * ...
 * argv[argc] - NIL
 *
 * @param argc - Count of arguments
 * @param argv - you know..
 * @return OK if success
 * @author nithin
 *
 * GLOBAL VARIABLES MODIFIED:
 *      <NONE>
 *
 * ERRORS REPORTED:
 *      - METADATA_SECURITY
 *      - ATTR_NOT_IN_REL
 *      - INSUFFICIENT_ATTRS
 *      - DB_NOT_OPEN
 *
 * ALGORITHM:
 *      1. Check for possible errors
 *      2. Create a char Array of size recLength
 *      3. Read each value from argv and convert it to a byte array
 *      4. Check if any attribute is repeated in the arguments using "hashing"
 *      5. Copy the byte array to correct location (using offset from attrList)
 *      6. Call InsertRec()
 *
 * IMPLEMENTATION NOTES:
 *      Record duplication is checked in InsertRec()
 *      Uses: OpenRel()
 */
int Insert(int argc, char **argv) {

    if (g_DBOpenFlag != OK) {
        return ErrorMsgs(DB_NOT_OPEN, g_PrintFlag);
    }

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

    if (g_CatCache[relNum].numAttrs != (argc - 2) / 2) {
        return ErrorMsgs(INSUFFICIENT_ATTRS, g_PrintFlag);
    }

    int i;
    /* Using calloc so that memory is initialized to zero.
     This is required while checking for duplicates in the relation */
    char *recPtr = (char *) calloc(g_CatCache[relNum].recLength, sizeof(char));
    struct attrCatalog *attr = NULL;

    //The offset of a record can be used to uniquely identify it
    int offsetMap[MAXRECORD] = { 0 };

    for (i = 2; i < argc; i += 2) {
        attr = getAttrCatalog(g_CatCache[relNum].attrList, argv[i]);
        if (attr == NULL) {
            return ErrorMsgs(ATTR_NOT_IN_REL, g_PrintFlag);
        }
        if (offsetMap[attr->offset] == 1) {
            return ErrorMsgs(ATTR_REPEATED, g_PrintFlag);
        } else {
            offsetMap[attr->offset] = 1;
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
                strncpy(recPtr + attr->offset, argv[i + 1], attr->length);
                break;
            default:
                break;
        }
    }

    //Duplicate checking done in InsertRec
    return InsertRec(relNum, recPtr);
}
