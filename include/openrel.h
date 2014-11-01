/*
 * openrel.h
 *
 *  Created on: 28-Oct-2014
 *      Author: Dheeraj
 */

#ifndef OPENREL_H_
#define OPENREL_H_

#include "cache.h"
#include "globals.h"
#include "readpage.h"
#include "error.h"
#include "helpers.h"
#include "defs.h"
#include "findrec.h" 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int OpenRel(char* RelName);

#endif /* OPENREL_H_ */