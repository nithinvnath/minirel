/*
 * print.h
 *
 *  Created on: 09-Nov-2014
 *      Author: nithin
 */

#ifndef PRINT_H_
#define PRINT_H_

#include "defs.h"
#include "error.h"
#include "globals.h"
#include "openrel.h"
#include "findrec.h"
#include "findrelnum.h"
#include "getnextrec.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_NUM_LENGTH  11

int max(int a, int b);

int Print(int argc, char **argv);

void printUnderScores(int count);

#endif /* PRINT_H_ */
