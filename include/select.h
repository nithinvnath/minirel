/*
 * select.h
 *
 *  Created on: 8-Nov-2014
 *      Author: Dheeraj
 */

#ifndef SELECT_H_
#define SELECT_H_

#include "defs.h"
#include "error.h"
#include "globals.h"
#include "openrel.h"
#include "findrelnum.h"
#include "create.h"
#include "insertrec.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Select (int argc, char **argv);

#endif /* SELECT_H_ */