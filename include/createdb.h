#ifndef CREATEDB_H_
#define CREATEDB_H_

#include "defs.h"
#include "error.h"
#include "globals.h"
#include "createcats.h"
#include "helpers.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int CreateDB(int argc, char **argv);

#endif /* CREATEDB_H_ */