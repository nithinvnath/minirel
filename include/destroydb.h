/*
 * createcats.c
 *
 *  Created on: 5-Nov-2014
 *      Author: Dheeraj
 */

#ifndef DESTROYDB_H_
#define DESTROYDB_H_

#include "defs.h"
#include "error.h"
#include "globals.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <string.h>

int delete_file(char* file_name, char* db_name);
int delete_dir(char* dir_name);
int DestroyDB(int argc,char **argv);


#endif /* DESTROYDB_H_ */