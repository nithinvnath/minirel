#include "../include/closedb.h"

/**
 * Closes the currently opened database and changes
 * the working directory to the original directory from which MINIREL was invoked
 *
 * @param argc
 * @param argv
 * @return OK or NOTOK
 */
int CloseDB(int argc, char **argv) {
    if (g_DBOpenFlag != OK) {
        return ErrorMsgs(DB_NOT_OPEN, g_PrintFlag);
    }
    if (CloseCats() == OK) {
        g_DBOpenFlag = NOTOK;
        chdir(g_InvokedDirectory);
        return OK;
    } else {
        return NOTOK;
    }
}

