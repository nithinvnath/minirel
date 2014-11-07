#include "../include/defs.h"
#include "../include/error.h"
#include "../include/globals.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * Closes the currently opened database and changes
 * the working directory to the original directory from which MINIREL was invoked
 *
 * @param argc
 * @param argv
 * @return OK or NOTOK
 */
int CloseDB(int argc, char **argv) {
    if (strcmp(g_db_name, "") == 0) {
        return ErrorMsgs(DB_NOT_OPEN, g_print_flag);
    }
    if (CloseCats() == OK) {
        strcpy(g_db_name, "");
        chdir(g_invoked_directory);
        return OK;
    } else {
        return NOTOK;
    }
}

