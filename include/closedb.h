/*
 * closedb.h
 *
 *  Created on: 9-Nov-2014
 *      Author: Dheeraj
 */

#ifndef CLOSEDB_H_
#define CLOSEDB_H_

#include "defs.h"
#include "error.h"
#include "globals.h"
#include "closecats.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int CloseDB(int argc, char **argv);

#endif /* CLOSEDB_H_ */