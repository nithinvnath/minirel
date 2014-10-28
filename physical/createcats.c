#include<stdio.h>
#include<filewrapper.c>

/**
 * Creates the system catalogs and places entries in the catalogs for the catalogs
 */

#define RELATION_CATALOG_NAME "relcat"
#define ATTRIBUTE_CATALOG_NAME "attrcat"

/**
 * Function: CreateCats()
 */
CreateCats() {
    //FIXME: how exactly should the dbname be passed?
    extern char *g_db_name;
    create_file(RELATION_CATALOG_NAME,g_db_name);

    printf("CreateCats \n ");

}
