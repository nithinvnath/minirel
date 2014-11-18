#include "../include/project.h"

/**
 * Implements the project command
 * Creates the result relation with the attributes given in argv,
 * then performs the projection
 * argv[0] - "project"
 * argv[1] - result relation
 * argv[2] - source relation
 * argv[3] - attribute name 1
 * ....
 * argv[argc] - NIL
 *
 * @param argc
 * @param argv
 * @return OK if success
 */
int Project(int argc, char **argv) {
    char sourceRel[RELNAME], destRel[RELNAME];

    /* Creating the new relation by calling create
     * Building the arguments to pass to create */
    strncpy(sourceRel, argv[2], RELNAME);
    strncpy(destRel, argv[1], RELNAME);

    if (OpenRel(sourceRel) == NOTOK) {
        return NOTOK;
    }

    int temp_flag = g_print_flag;

    int sourceRelNum = FindRelNum(sourceRel);
    struct attrCatalog *attrList = g_catcache[sourceRelNum].attrList;

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

    for (i = 2, j = 3; i < argc - 1; i += 2, ++j) {
        createArgs[i] = (char *) malloc(strlen(argv[j]) * sizeof(char));
        attr = getAttrCatalog(g_catcache[sourceRelNum].attrList, argv[j]);
        if (attr == NULL) {
            return ErrorMsgs(ATTRNOEXIST, g_print_flag);
        }
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
        char *destRec = (char *) calloc(g_catcache[destRelNum].recLength, sizeof(char));
        int offset = 0;
        struct attrCatalog *attr = *attrArray;
        while (attr) { //Take each attribute in dest relation
            strncpy(destRec + offset, recPtr + attr->offset, attr->length);
            //Copy the bytes corresponding to the attribute into dest record
            offset += attr->length;
            attr = attr->next;
        }
        //Temporarily disable the error print flag so that duplicate won't cause error.
        g_print_flag = 0;
        InsertRec(destRelNum, destRec);
        g_print_flag = temp_flag;
        free(destRec);

        startRid = *foundRid;
        free(foundRid);
    }
    return OK;
}

/**
 * Gets the attribute catalog using the attribute name
 *
 * @param attrList
 * @param attrName
 * @return the attrCatalog struct
 */
struct attrCatalog* getAttrCatalog(struct attrCatalog* attrList, char *attrName) {
    while (attrList != NULL) {
        if (strcmp(attrName, attrList->attrName) == 0) {
            break;
        }
        attrList = attrList->next;
    }
    return attrList;
}

