#include "../include/createdb.h"

/**
 * Creates a new database. It creates the relation and attribute catalogs and loads them with
 * the appropriate initial information.
 *
 * @param argc
 * @param argv
 * @return OK or NOTOK
 */
int CreateDB(int argc, char **argv) {
    if (argc < 2) {
        return ErrorMsgs(ARGC_INSUFFICIENT, g_print_flag);
    }
    if (g_db_open_flag == OK) {
        return ErrorMsgs(DB_NOT_CLOSED, g_print_flag);
    }

    char dbname[RELNAME], dbpath[MAXPATH];
    separate_db_path(argv[1], dbpath, dbname);

    /* Stores the current working directory to be changed once done */
    getcwd(g_invoked_directory, MAXPATH);

    chdir(dbpath);

    if (mkdir(dbname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
        chdir(g_invoked_directory);
        if (errno == EEXIST) {
            return ErrorMsgs(DB_ALREADY_EXISTS, g_print_flag);
        } else {
            return ErrorMsgs(FILE_SYSTEM_ERROR, g_print_flag);
        }
    }
    chdir(dbname);
    g_db_open_flag = OK;
    int returnflag = CreateCats();

    g_db_open_flag = NOTOK;
    chdir(g_invoked_directory);

    return returnflag;
}
