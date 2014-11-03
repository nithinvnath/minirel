/*
 * opencats.h
 *
 *  Created on: 31-Oct-2014
 *      Author: Dheeraj
 */

#ifndef CREATECATS_H_
#define CREATECATS_H_

#include "error.h"
#include "defs.h"
#include "globals.h"
#include "helpers.h"
 
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

int CreateRelCat();
int CreateAttrCat();
int CreateCats();

#endif /* CREATECATS_H_ */