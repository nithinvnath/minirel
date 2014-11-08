/*
 * destroy.h
 *
 *  Created on: 9-Nov-2014
 *      Author: Dheeraj
 */

#ifndef DESTROY_H_
#define DESTROY_H_

#include "defs.h"
#include "error.h"
#include "globals.h"
#include "delete.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int Destroy(int argc, char** argv);

#endif /* DESTROY_H_ */