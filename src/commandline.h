/*
 * commandline.h
 *
 *  Created on: 2016/03/11
 *      Author: kinoshita.akihiro
 *
 *  2016/04/11 kinoshita
 *  	modified commandline_get_arg()
 *  2016/10/24 kinoshita
 *  	collected command names and command functions together
 *  2016/11/09 kinoshita
 *  	rearranged the order of arguments in "commandline_get_arg"
 *
 */

#ifndef COMMANDLINE_H_
#define COMMANDLINE_H_

#include <stdbool.h>

#define COMMANDLINE_NARG_MAX 10
#define COMMANDLINE_ARGLEN_MAX 40

typedef struct{
	char *name; // command name
	void (*func)(void); // command function
}COMMANDLINE_SET;

extern const int n_commandline;

extern COMMANDLINE_SET commandline_sets[];

// get command, and execute command function
// argument : command string (command argument should be separated by space character)
// return : true -> command execution succeeded
//          false -> illegal command, or empty string
bool commandline_input(char *cmd);

// get command argument
// argument : 
//     iarg : argument position (0 -> command token)
//     arg : argument string
//     arglen : max length of "arg"
// return :
//		true : successfully got an argument
// 		false : iarg was out of range
bool commandline_get_arg(int iarg, char *arg, int arglen);

// get number of arguments (including command token)
int commandline_narg(void);


#endif /* COMMANDLINE_H_ */
