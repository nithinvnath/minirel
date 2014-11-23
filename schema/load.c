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
 */
//FIXME should the file operations be in this layer?
int Load(int argc, char **argv) {
    char relName[RELNAME];
    strncpy(relName, argv[1], RELNAME);

    if (strcmp(relName, ATTRCAT) == 0 || strcmp(relName, RELCAT) == 0) {
        return ErrorMsgs(METADATA_SECURITY, g_print_flag);
    }

    if (OpenRel(relName) == NOTOK) {
        return NOTOK;
    }

    int relNum = FindRelNum(relName);
    if (g_catcache[relNum].numRecs > 0) {
        return ErrorMsgs(REL_NOT_EMPTY, g_print_flag);
    }

    int fd = open(argv[2], O_RDONLY);
    if (fd < 0) {
        return ErrorMsgs(INVALID_FILE, g_print_flag);
    }

    int recLength = g_catcache[relNum].recLength;
    char *newRec = (char *) calloc(recLength, sizeof(char));

    g_check_duplicate_tuples = NOTOK;
    while (read(fd, newRec, recLength) == recLength) {
        if (InsertRec(relNum, newRec) != OK) {
            return NOTOK;
        }
    }
    g_check_duplicate_tuples = OK;

    return OK; /* all's fine */
}

