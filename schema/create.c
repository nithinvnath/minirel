#include "../include/create.h"

/**
 * Creates a new relation with the specified name and attributes.
 *
 * @param argc
 * @param argv
 * @return
 */
//TODO Should attribute and relation names be case sensitive
int Create(int argc, char **argv) {

    int offset, length, i;
    char type, attrName[RELNAME + 2], relName[RELNAME + 2], attrFormat[3];
    strcpy(relName, argv[1]);

    if (isValidString(relName) == NOTOK) {
        return ErrorMsgs(INVALID_ATTR_NAME, g_print_flag);
    }

    /* To check if relation exists, we will call openRel
     * after turning off the error print flag temporarily. */
    int printFlag = g_print_flag;
    g_print_flag = 0;
    if (OpenRel(relName) == OK) {
        g_print_flag = printFlag;
        return ErrorMsgs(REL_ALREADY_EXISTS, g_print_flag);
    } else {
        g_print_flag = printFlag;
    }
    //FIXME should file i/o be in physical layer?
    //Creating the file for relation and adding a page
    int fd = open(relName, O_RDWR, S_IRWXU);
    char *slotmap = (char *) malloc((PAGESIZE - MAXRECORD) * sizeof(char));
    convertIntToByteArray(0, slotmap);
    write(fd, slotmap, (PAGESIZE - MAXRECORD));
    close(fd);
    free(slotmap);
    return 1;
    /* Creating the template attribute catalog records */
    char **attrCatArgs;
    int attrCatArraySize;
    createTemplate(ATTRCAT_CACHE, &attrCatArgs, ATTRCAT, &attrCatArraySize);

    int numAttrs;
    /* Iterate through each attribute and insert it to attrcat table */
    for (i = 2, numAttrs = 0, offset = 0; i < argc; i = i + 2, numAttrs++) {
        attrName[0] = '\"';
        strncpy(attrName + 1, argv[i], RELNAME);
        attrName[strlen(attrName)] = '\"'; //To enclose it in quotes

        strcpy(attrFormat, argv[i + 1]);
        type = attrFormat[0];
        if (type != INTEGER && type != STRING && type != FLOAT) {
            return ErrorMsgs(INVALID_ATTR_TYPE, g_print_flag);
        }
        length = getSizeOfAttr(attrFormat);
        if (length > MAX_STRING_SIZE) {
            return ErrorMsgs(MAX_STRING_EXCEEDED, g_print_flag);
        }
        int j;

        /* Filling the attribute catalog record template */
        for (j = 2; j < attrCatArraySize; j += 2) {
            if (strcmp(attrCatArgs[j], OFFSET) == 0) {
                sprintf(attrCatArgs[j + 1], "%d", offset);
            } else if (strcmp(attrCatArgs[j], TYPE) == 0) {
                sprintf(attrCatArgs[j + 1], "%d", type);
            } else if (strcmp(attrCatArgs[j], LENGTH) == 0) {
                sprintf(attrCatArgs[j + 1], "%d", length);
            } else if (strcmp(attrCatArgs[j], ATTRNAME) == 0) {
                strcpy(attrCatArgs[j + 1], attrName);
//                printf("%s\n", attrCatArgs[j+1]);
            } else {
                sprintf(attrCatArgs[j + 1],"\"%s\"",relName);
//                strcpy(attrCatArgs[j + 1], relName);
            }
        }
        offset += length;
        Insert(attrCatArraySize, attrCatArgs);
    }

    /* Free the attrCatArgs*/
    freeAllottedMem(attrCatArgs, attrCatArraySize);

    /* Insert the data into relcat */
    char **relcatArgs;
    int relcatArraySize;
    createTemplate(RELCAT_CACHE, &relcatArgs, RELCAT, &relcatArraySize);

    //Fill the template
    int j, recsPerPg;
    recsPerPg = offset / MAXRECORD;

    for (j = 2; j < relcatArraySize; j += 2) {
        if (strcmp(relcatArgs[j], RECLENGTH) == 0) {
            sprintf(relcatArgs[j + 1], "%d", offset);
        } else if (strcmp(relcatArgs[j], RECSPERPG) == 0) {
            sprintf(relcatArgs[j + 1], "%d", recsPerPg);
        } else if (strcmp(relcatArgs[j], NUMATTRS) == 0) {
            sprintf(relcatArgs[j + 1], "%d", numAttrs);
        } else if (strcmp(relcatArgs[j], NUMRECS) == 0) {
            sprintf(relcatArgs[j + 1], "%d", 0);
        } else if (strcmp(relcatArgs[j], NUMPGS) == 0) {
            sprintf(relcatArgs[j + 1], "%d", 1);
        } else {
            sprintf(relcatArgs[j + 1], "\"%s\"", relName);
        }
    }
    Insert(relcatArraySize, relcatArgs);

    freeAllottedMem(relcatArgs, relcatArraySize);

    return OK; /* all's fine */
}
/**
 *
 * @param cacheIndex
 * @param args
 * @param relName
 * @param arraySize
 */
void createTemplate(int cacheIndex, char ***args, char *relName, int *arraySize) {
    int i;
    struct attrCatalog *attrList = g_catcache[cacheIndex].attrList;
    *arraySize = (2 * g_catcache[cacheIndex].numAttrs + 2);

    *args = (char **) malloc(*arraySize * sizeof(char *));
    (*args)[0] = (char *) malloc(strlen("_insert") * sizeof(char));
    strcpy((*args)[0], "_insert");
    (*args)[1] = (char *) malloc(strlen(relName) * sizeof(char));
    strcpy((*args)[1], relName);

    i = 2;
    while (attrList != NULL) {
        (*args)[i] = (char *) malloc(strlen(attrList->attrName) * sizeof(char));
        (*args)[i + 1] = (char *) malloc((attrList->length + 2) * sizeof(char));
        strcpy((*args)[i], attrList->attrName);
        i += 2;
        attrList = attrList->next;
    }
}

/**
 *
 * @param args
 * @param arraySize
 */
void freeAllottedMem(char **args, int arraySize) {
    int i;
    for (i = 0; i < arraySize; ++i) {
        free(args[i]);
    }
    free(args);
}
