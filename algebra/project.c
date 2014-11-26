#include "../include/project.h"

/**
 * Implements the project command
 * Creates the result relation with the attributes given in argv,
 * then performs the projection
 *
 * argv[0] - "project"
 * argv[1] - result relation
 * argv[2] - source relation
 * argv[3] - attribute name 1
 * ....
 * argv[argc] - NIL
 *
 * @param argc - Argument count
 * @param argv
 * @return OK if success
 *
 * GLOBAL VARIABLES MODIFIED
 *      - g_PrintFlag (but switches it back)
 *
 * ERRORS REPORTED:
 *      - DB_NOT_OPEN
 *      - ATTRNOEXIST
 *
 * ALGORITHM:
 *      1. Checks if DB is open and if sourceRel exists
 *      2. Creates a new destination relation using Create()
 *          - This is  done by manually creating arguments to be passed.
 *      3. Open the destination relation
 *      4. Iterate over each record in source relation
 *      5.      Take each attribute in destination relation
 *      6.          Directly copy the bytes from source relation to a byte
 *                      array at the correct offset
 *      7.      Insert the byte array by calling InsertRec
 *
 * IMPLEMENTATION NOTES:
 *      Uses: OpenRel(), FindRelNum(), Create(), GetNextRec(), InsertRec()
 */
int Project(int argc, char **argv) {
    if (g_DBOpenFlag != OK) {
        return ErrorMsgs(DB_NOT_OPEN, g_PrintFlag);
    }
    char sourceRel[RELNAME], destRel[RELNAME];

    /* Creating the new relation by calling create
     * Building the arguments to pass to create */
    strncpy(sourceRel, argv[2], RELNAME - 1);
    strncpy(destRel, argv[1], RELNAME - 1);

    if (OpenRel(sourceRel) == NOTOK) {
        return NOTOK;
    }

    int sourceRelNum = FindRelNum(sourceRel);
    struct attrCatalog *attrList = g_CatCache[sourceRelNum].attrList;

    int i, j, numCreateArgs = (argc - 3) * 2 + 2;
    char **createArgs = (char **) malloc(numCreateArgs * sizeof(char *));
    createArgs[0] = (char *) malloc(strlen("create") * sizeof(char));
    strcpy(createArgs[0], "create");
    createArgs[1] = (char *) malloc(strlen(destRel) * sizeof(char));
    strcpy(createArgs[1], destRel);
    struct attrCatalog *attr;

    struct attrCatalog **attrArray = (struct attrCatalog**) malloc(
            (argc - 3) * sizeof(struct attrCatalog*));
    //Stores the array of attributes in dest relation in order they appear. To be used later

    for (i = 2, j = 3; i <= 2 * argc - 6; i += 2, ++j) {
        createArgs[i] = (char *) malloc(strlen(argv[j]) * sizeof(char));
        attr = getAttrCatalog(g_CatCache[sourceRelNum].attrList, argv[j]);
        if (attr == NULL) {
            return ErrorMsgs(ATTRNOEXIST, g_PrintFlag);
        }
        strcpy(createArgs[i], attr->attrName);
        createArgs[i + 1] = (char *) calloc(4, sizeof(char));
        if (attr->type == STRING) {
            sprintf(createArgs[i + 1], "s%d", attr->length);
        } else {
            createArgs[i + 1][0] = attr->type;
        }
        attrArray[j - 3] = attr;
    }
    if (Create(numCreateArgs, createArgs) != OK) {
        freeAllottedMem(createArgs, numCreateArgs);
        return NOTOK;
    }
    freeAllottedMem(createArgs, numCreateArgs);

    /* Inserting data to the new relation */
    Rid startRid = { 0, 0 }, *foundRid;
    char *recPtr;
    if (OpenRel(destRel) == NOTOK) {
        return NOTOK;
    }
    int destRelNum = FindRelNum(destRel);

    while (GetNextRec(sourceRelNum, &startRid, &foundRid, &recPtr) == OK) {
        //Iterate through each record in source rel
        char *destRec = (char *) calloc(g_CatCache[destRelNum].recLength, sizeof(char));
        int offset = 0;
        i = 0;
        struct attrCatalog *attr = attrArray[i];
        while (i < j - 3) { //Take each attribute in dest relation
            memcpy(destRec + offset, recPtr + attr->offset, attr->length);
            //Copy the bytes corresponding to the attribute into dest record
            i++;
            offset += attr->length;
            attr = attrArray[i];
        }
        //Temporarily disable the error print flag so that duplicate won't cause error.
        int tempFlag = g_PrintFlag;
        g_PrintFlag = 1;
        InsertRec(destRelNum, destRec);
        g_PrintFlag = tempFlag;
        free(destRec);

        startRid = *foundRid;
        free(foundRid);
    }
    return OK;
}
