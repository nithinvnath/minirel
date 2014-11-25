#include "../include/create.h"

#define _DESTROY  "_destroy"

/**
 * Creates a new relation with the specified name and attributes.
 *
 * @param argc
 * @param argv
 * @return
 */
int Create(int argc, char **argv) {

    if (g_DBOpenFlag != OK) {
        return ErrorMsgs(DB_NOT_OPEN, g_PrintFlag);
    }

    int offset, length, i;
    char type, attrName[RELNAME], relName[RELNAME], attrFormat[4];

    if (isValidString(argv[1]) == NOTOK) {
        return ErrorMsgs(INVALID_ATTR_NAME, g_PrintFlag);
    }
    strcpy(relName, argv[1]);

    /* To check if relation exists, we will call openRel
     * after turning off the error print flag temporarily. */
    int printFlag = g_PrintFlag;
    g_PrintFlag = 1;
    if (OpenRel(relName) != NOTOK) {
        g_PrintFlag = printFlag;
        return ErrorMsgs(REL_ALREADY_EXISTS, g_PrintFlag);
    } else {
        g_PrintFlag = printFlag;
    }
    //Creating the file for relation and adding a page
    int fd = open(relName, O_RDWR | O_CREAT, S_IRWXU);
    char *slotMap = (char *) malloc((PAGESIZE - MAXRECORD) * sizeof(char));
    convertIntToByteArray(0, slotMap);
    write(fd, slotMap, (PAGESIZE - MAXRECORD));
    close(fd);
    free(slotMap);
    /* Creating the template attribute catalog records */
    char **attrCatArgs;
    int attrCatArraySize;
    createTemplate(ATTRCAT_CACHE, &attrCatArgs, ATTRCAT, &attrCatArraySize);

    int numAttrs;
    /* Iterate through each attribute and insert it to attrcat table */
    for (i = 2, numAttrs = 0, offset = 0; i < argc; i = i + 2, numAttrs++) {
        strncpy(attrName, argv[i], RELNAME-1);

        strcpy(attrFormat, argv[i + 1]);
        type = attrFormat[0];
        if (type != INTEGER && type != STRING && type != FLOAT) {
            return ErrorMsgs(INVALID_ATTR_TYPE, g_PrintFlag);
        }
        length = getSizeOfAttr(attrFormat);
        if (length > MAX_STRING_SIZE) {
            return ErrorMsgs(MAX_STRING_EXCEEDED, g_PrintFlag);
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
            } else {
                sprintf(attrCatArgs[j + 1], "%s", relName);
            }
        }
        offset += length;
        if(offset>MAXRECORD){
            char **destroy_args = (char **)malloc(sizeof(char*)*2);
            destroy_args[0] = (char *) malloc(sizeof(char)*strlen(_DESTROY));
            destroy_args[1] = (char *) malloc(sizeof(char)*strlen(relName));
            sprintf(destroy_args[0],"%s",_DESTROY);
            sprintf(destroy_args[1],"%s",relName);
            Destroy(2,(char **)destroy_args);
            free(destroy_args[0]);
            free(destroy_args[1]);
            free(destroy_args);
            return ErrorMsgs(PAGE_OVERFLOW,g_PrintFlag);
        }
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
    recsPerPg = MAXRECORD / offset < 32 ? MAXRECORD / offset : 32;

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
            sprintf(relcatArgs[j + 1], "%s", relName);
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
    struct attrCatalog *attrList = g_CatCache[cacheIndex].attrList;
    *arraySize = (2 * g_CatCache[cacheIndex].numAttrs + 2);

    *args = (char **) malloc(*arraySize * sizeof(char *));
    (*args)[0] = (char *) malloc(strlen("_insert") * sizeof(char));
    strcpy((*args)[0], "_insert");
    (*args)[1] = (char *) malloc(strlen(relName) * sizeof(char));
    strcpy((*args)[1], relName);

    i = 2;
    while (attrList != NULL) {
        (*args)[i] = (char *) malloc(strlen(attrList->attrName) * sizeof(char));
        (*args)[i + 1] = (char *) malloc((attrList->length) * sizeof(char));
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
