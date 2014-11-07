/*
 * insert.h
 *
 *  Created on: 08-Nov-2014
 *      Author: nithin
 */

#ifndef INSERT_H_
#define INSERT_H_

#include "../include/defs.h"
#include "../include/error.h"
#include "../include/globals.h"
#include "../include/helpers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct attrCatalog* getAttrCatalog(struct attrCatalog *attrList, char *attrName);

void removeQuotes(char *quotedString);

int Insert(int argc, char **argv);

#endif /* INSERT_H_ */
