/*
 * createcats.c
 *
 *  Created on: 7-Nov-2014
 *      Author: Dheeraj
 */

#include "../include/quit.h"

/*
 * Function:  Quit()
 * ------------------------
 * terminates the program after closing database, if open
 *
 * argv[0] = “quit”
 * argv[argc] = NIL
 * 
 */

void Quit (int argc, char **argv)
{
    if(strcmp(g_db_name,"") != 0)
        CloseDB();
    exit(0);
}


