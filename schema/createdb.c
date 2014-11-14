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
    if(argc < 2){
        return ErrorMsgs(ARGC_INSUFFICIENT, g_print_flag);
    }
    if (strcmp(g_db_name, "") != 0) {
        return ErrorMsgs(DB_NOT_CLOSED, g_print_flag);
    }

    char dbname[RELNAME], dbpath[MAXPATH];
    separate_db_path(argv[1], dbpath, dbname);

    /* Stores the current working directory to be changed once done */
    getcwd(g_invoked_directory, MAXPATH);

    chdir(dbpath);

    if (mkdir(dbname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
        if (errno == EEXIST) {
            return ErrorMsgs(DB_ALREADY_EXISTS, g_print_flag);
        } else {
            return ErrorMsgs(FILE_SYSTEM_ERROR, g_print_flag);
        }
    }
    chdir(dbname);
    strcpy(g_db_name, dbname);
    int returnflag = CreateCats();

    strcpy(g_db_name, "");
    chdir(g_invoked_directory);

    return returnflag;
}
