#ifndef UTILS_H
#define UTILS_H

#include "../include/types.h"

/** 
 * Wrapper for popen
 * 
 * Command - String with the command to execute
 * Output - String where the output of the command is saved. Memory is allocated inside.
 * 
 * Returns - OK or ERROR
*/
int exec(char *command, char **output);

#endif