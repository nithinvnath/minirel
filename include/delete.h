/*
 * delete.h
 *
 *  Created on: 8-Nov-2014
 *      Author: Dheeraj
 */

#ifndef DELETE_H_
#define DELETE_H_

#include "defs.h"
#include "error.h"
#include "globals.h"
#include "openrel.h"
#include "findrelnum.h"
#include "deleterec.h"
#include "helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Delete (int argc, char **argv);

#endif /* DELETE_H_ */