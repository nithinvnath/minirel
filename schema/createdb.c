#include "../include/defs.h"
#include "../include/error.h"
#include "../include/globals.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

/**
 * Creates a new database. It creates the relation and attribute catalogs and loads them with
 * the appropriate initial information.
 *
 * @param argc
 * @param argv
 * @return OK or NOTOK
 */
int CreateDB(int argc, char **argv) {

    char current_db_name[RELNAME];
    strcpy(current_db_name,g_db_name);

    if (mkdir(argv[0], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
        if (errno == EEXIST) {
            return ErrorMsgs(DB_ALREADY_EXISTS, g_print_flag);
        } else {
            return ErrorMsgs(FILE_SYSTEM_ERROR, g_print_flag);
        }
    }
    strcpy(g_db_name, argv[2]);
    int returnflag = CreateCats();

    strcpy(g_db_name,current_db_name);
    return returnflag;
}
