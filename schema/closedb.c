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
    if (!g_db_open_flag) {
        return ErrorMsgs(DB_NOT_OPEN, g_print_flag);
    }
    if (CloseCats() == OK) {
        g_db_open_flag = 0;
        chdir(g_invoked_directory);
        return OK;
    } else {
        return NOTOK;
    }
}

