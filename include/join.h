/*
 * join.h
 *
 *  Created on: 8-Nov-2014
 *      Author: Dheeraj
 */

#ifndef JOIN_H_
#define JOIN_H_

#include "defs.h"
#include "error.h"
#include "globals.h"
#include "insertrec.h"
#include "getnextrec.h"
#include "openrel.h"
#include "findrelnum.h"
#include "create.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy_binary_array(char *dest, char *source, int length);
int Join (int argc, char **argv);

#endif /* JOIN_H_ */