/*
 * project.h
 *
 *  Created on: 08-Nov-2014
 *      Author: nithin
 */

#ifndef PROJECT_H_
#define PROJECT_H_

#include "../include/defs.h"
#include "../include/error.h"
#include "../include/globals.h"
#include "../include/create.h"
#include "../include/getnextrec.h"
#include "../include/findrelnum.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct attrCatalog* getAttrCatalog(struct attrCatalog* attrList, char *attrName);

int Project(int argc, char **argv);

#endif /* PROJECT_H_ */
