/*
 * create.h
 *
 *  Created on: 08-Nov-2014
 *      Author: nithin
 */

#ifndef CREATE_H_
#define CREATE_H_

#include "../include/defs.h"
#include "../include/error.h"
#include "../include/globals.h"
#include "../include/helpers.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define OFFSET      "offset"
#define LENGTH      "length"
#define TYPE        "type"
#define ATTRNAME    "attrName"

#define RECLENGTH "recLength"
#define RECSPERPG "recsPerPg"
#define NUMATTRS  "numAttrs"
#define NUMRECS   "numRecs"
#define NUMPGS    "numPgs"

int Create(int argc, char **argv);

void createTemplate(int cacheIndex, char ***args, char *relName, int *arraySize);

void freeAllottedMem(char **args, int arraySize);

#endif /* CREATE_H_ */
