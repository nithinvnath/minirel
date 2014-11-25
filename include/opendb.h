/*
 * opendb.h
 *
 *  Created on: 5-Nov-2014
 *      Author: Dheeraj
 */

#ifndef OPENDB_H_
#define OPENDB_H_

#include "defs.h"
#include "error.h"
#include "globals.h"
#include "opencats.h"
 
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>

int OpenDB (int argc, char **argv);

#endif /* OPENDB_H_ */