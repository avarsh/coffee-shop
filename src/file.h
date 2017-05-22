#ifndef FILE_H
#define FILE_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

/*
 * Functions to load user configurations
 * -------------------------------------
 */

int load_config(double* volume_array, int array_size);
int write_config(double* volume_array, int array_size);

int open_file(FILE** config_file, int write_mode);

#endif // FILE_H
