/*
 * closerel.h
 *
 *  Created on: 31-Oct-2014
 *      Author: Dheeraj
 */

#ifndef CLOSEREL_H_
#define CLOSEREL_H_

#include "error.h"
#include "defs.h"
#include "globals.h"
#include "helpers.h"
#include "flushpage.h"
#include "findrec.h"
#include "writerec.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
int CloseRel(int relNum);

#endif /*OPENREL_H_*/