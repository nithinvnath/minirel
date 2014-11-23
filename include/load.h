/*
 * load.h
 *
 *  Created on: 09-Nov-2014
 *      Author: nithin
 */

#ifndef LOAD_H_
#define LOAD_H_

#include "defs.h"
#include "error.h"
#include "globals.h"
#include "openrel.h"
#include "findrelnum.h"
#include "insertrec.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int Load(int argc, char **argv);

#endif /* LOAD_H_ */
