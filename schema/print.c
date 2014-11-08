#include "../include/print.h"

/**
 * Prints out the contents of the specified relation in the form of a table
 * argv[0]      - "print"
 * argv[1]      - relation name
 * argv[argc]   - NIL
 *
 * @param argc
 * @param argv
 * @return OK or NOTOK
 */
int Print(int argc, char **argv) {
    char relName[20];
    strncpy(relName, argv[1], RELNAME);

    if (OpenRel(relName) != OK) {
        return NOTOK;
    }

    int relNum = FindRelNum(relName);

    struct attrCatalog *list, *attrList = g_catcache[relNum].attrList;
    list = attrList;
    int tableRowLength = 2;
    printf("| ");
    while (list != NULL) {
        printf("%*s | ", max(strlen(list->attrName), list->length), list->attrName);
        tableRowLength += (3 +  max(strlen(list->attrName), list->length));
        list = list->next;
    }
    printUnderScores(tableRowLength);
    Rid *foundRid, startRid = { 0, 0 };
    char *recPtr = malloc(sizeof(char) * g_catcache[relNum].recLength);
    int intval;
    float floatval;
    char string[MAX_STRING_SIZE];
    while (GetNextRec(relNum, &startRid, &foundRid, &recPtr) == OK) {
        list = attrList;
        printf("| ");
        while (list != NULL) {
            switch (list->type) {
                case INTEGER:
                    intval = readIntFromByteArray(recPtr, list->offset);
                    printf("%*d | ", max(strlen(list->attrName), list->length), intval);
                    break;
                case FLOAT:
                    floatval = readFloatFromByteArray(recPtr, list->offset);
                    printf("%*f | ", max(strlen(list->attrName), list->length), floatval);
                    break;
                case STRING:
                    readStringFromByteArray(string, recPtr, list->offset, list->length);
                    printf("%*s | ", max(strlen(list->attrName), list->length), string);
                    break;
            }
            list = list->next;
        }
        printUnderScores(tableRowLength);
        startRid = *foundRid;
        free(foundRid);
    }

    free(recPtr);
    return OK; /* all's fine */
}

int max(int a, int b) {
    return a > b ? a : b;
}

void printUnderScores(int count){
    printf("\n");
    while(count-->0){
        printf("_");
    }
    printf("\n");
}
