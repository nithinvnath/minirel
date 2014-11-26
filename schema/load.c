#include "../include/load.h"

/**
 * This routine loads the specified relation, which must already have been created,
 * with data from the specified file
 * argv[0] - "load"
 * argv[1] - relation name
 * argv[2] - data file name (full path)
 *
 * @param argc
 * @param argv
 * @return OK or NOTOK
 * @author nithin
 *
 * GLOBAL VARIABLES MODIFIED:
 *      g_CheckDuplicateTuples
 *
 * ERRORS REPORTED:
 *      DB_NOT_OPEN
 *      METADATA_SECURITY
 *      REL_NOT_EMPTY
 *      INVALID_FILE
 *
 * ALGORITHM:
 *      1. Check if DB is open and if trying to loaf  into attrcat ot relcat
 *      2. Open relation with given name
 *      3. Check if the relation is empty
 *      4. Open the file given
 *      5. Read a byte array of recLength size and call InsertRec()
 *
 * IMPLEMENTATION NOTES:
 *      Uses InsertRec(), OpenRel()
 *
 */
int Load(int argc, char **argv) {
    if (g_DBOpenFlag != OK) {
        return ErrorMsgs(DB_NOT_OPEN, g_PrintFlag);
    }
    char relName[RELNAME];
    strncpy(relName, argv[1], RELNAME);

    if (strcmp(relName, ATTRCAT) == 0 || strcmp(relName, RELCAT) == 0) {
        return ErrorMsgs(METADATA_SECURITY, g_PrintFlag);
    }

    if (OpenRel(relName) == NOTOK) {
        return NOTOK;
    }

    int relNum = FindRelNum(relName);
    if (g_CatCache[relNum].numRecs > 0) {
        return ErrorMsgs(REL_NOT_EMPTY, g_PrintFlag);
    }

    int fd = open(argv[2], O_RDONLY);
    if (fd < 0) {
        return ErrorMsgs(INVALID_FILE, g_PrintFlag);
    }

    int recLength = g_CatCache[relNum].recLength;
    char *newRec = (char *) calloc(recLength, sizeof(char));

    g_CheckDuplicateTuples = NOTOK;
    while (read(fd, newRec, recLength) == recLength) {
        if (InsertRec(relNum, newRec) != OK) {
            return NOTOK;
        }
    }
    g_CheckDuplicateTuples = OK;

    return OK; /* all's fine */
}

