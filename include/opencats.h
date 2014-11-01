/*
 * opencats.h
 *
 *  Created on: 30-Oct-2014
 *      Author: Dheeraj
 */

#ifndef OPENCATS_H_
#define OPENCATS_H_

#include "globals.h"
#include "defs.h"
#include "cache.h"
#include "buffer.h"
#include "globals.h"
#include "readpage.h"
#include "helpers.h"
#include "findrec.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 

struct attrCatalog* create_attr_cat_attrcat();
struct attrCatalog* create_attr_cat_relcat();

int OpenCats();

#endif  /* OPENCATS_H_ */