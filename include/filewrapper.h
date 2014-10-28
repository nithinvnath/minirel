#ifndef FILEWRAPPER_H_
#define FILEWRAPPER_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

#define PATH ".minirel_data"
#define NAME_MAX_LENGTH 50

int create_file(char*, char*);
int delete_file(char*, char*);
int delete_dir(char*);
int append_to_file(char*, char*, char*, int);
int write_to_file(char*, char*, long, char*, int);
int read_from_file(char*, char*, long, char*, int);

#endif