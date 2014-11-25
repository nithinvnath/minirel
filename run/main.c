#include <stdio.h>
#include "../include/globals.h"

extern parser();

int main() {
    printf("Welcome to MINIREL database system\n\n");
    /* Initialize the global variables */
    g_db_open_flag = NOTOK;
    g_print_flag = OK;
    /*-------------------------------- */
    parser();
    printf("\n\nGoodbye from MINIREL\n");
    return 0;
}
