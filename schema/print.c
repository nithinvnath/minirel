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
 *
 * @author nithin
 *
 * GLOBAL VARIABLES MODIFIED:
 *      <none>
 *
 * ERRORS REPORTED:
 *      DB_NOT_OPEN
 *      RELNOEXIST
 *
 * ALGORITHM:
 *      1. Check for the usual DB OPEN error
 *      2. Open the relation
 *      3. Get the attribute list
 *      4. Print all the attributes
 *      5. Print all the records as separate rows
 *
 * IMPLEMENTATION NOTES
 *      Assumes that float values will fit within 11 characters. Alignment will go wary otherwise
 *      Didn't want to give too much width to the float columns as I hope those will be rare cases
 *      (A case of CISC vs RISC?)
 *
 *      Uses OpenRel(), GetNextRec()
 */
int Print(int argc, char **argv) {
    if (g_DBOpenFlag != OK) {
        return ErrorMsgs(DB_NOT_OPEN, g_PrintFlag);
    }
    char relName[20];
    strncpy(relName, argv[1], RELNAME);

    if (OpenRel(relName) == NOTOK) {
        return NOTOK;
    }

    int relNum = FindRelNum(relName);
    if (relNum == NOTOK)
        return ErrorMsgs(RELNOEXIST, g_PrintFlag);

    struct attrCatalog *list, *attrList = g_CatCache[relNum].attrList;
    list = attrList;
    int tableRowLength = 2;

    /* Print the header row */
    printf("| ");
    while (list != NULL) {
        int width = list->type == STRING ? list->length : MAX_NUM_LENGTH;
        printf("%*s | ", max(strlen(list->attrName), width), list->attrName);
        tableRowLength += (3 + max(strlen(list->attrName), width));
        list = list->next;
    }
    printUnderScores(tableRowLength);

    Rid *foundRid, startRid = { 0, 0 };
    char *recPtr = malloc(sizeof(char) * g_CatCache[relNum].recLength);
    int intval;
    float floatval;
    char string[MAX_STRING_SIZE];
    while (GetNextRec(relNum, &startRid, &foundRid, &recPtr) == OK) { //Fetch each record
        list = attrList;
        printf("| ");
        while (list != NULL) {
            int width = list->type == STRING ? list->length : MAX_NUM_LENGTH;
            switch (list->type) {
                case INTEGER:
                    intval = readIntFromByteArray(recPtr, list->offset);
                    printf("%*d | ", max(strlen(list->attrName), width), intval);
                    break;
                case FLOAT:
                    floatval = readFloatFromByteArray(recPtr, list->offset);
                    printf("%*g | ", max(strlen(list->attrName), width), floatval);
                    break;
                case STRING:
                    readStringFromByteArray(string, recPtr, list->offset, list->length);
                    printf("%*s | ", max(strlen(list->attrName), list->length), string);
                    break;
            }
            list = list->next;
        }
        printUnderScores(tableRowLength - 1); //Printing a line to separate rows
        startRid = *foundRid;
        free(foundRid);
    }

    free(recPtr);
    return OK; /* all's fine */
}

/* Small max function*/
int max(int a, int b) {
    return a > b ? a : b;
}

/**
 *  Does exactly what it says.
 *  Prints a newline then 'count' number of underscores and another newline
 *
 * @param count
 */
void printUnderScores(int count) {
    printf("\n");
    while (count-- > 0) {
        printf("_");
    }
    printf("\n");
}
