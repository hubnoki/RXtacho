/*
 * commandline.c
 *
 *  Created on: 2016/03/11
 *      Author: kinoshita.akihiro
 *
 *  2016/04/11 kinoshita
 *  	modified commandline_get_arg()
 *  2016/09/18 kinoshita
 *  	modified commandline_get_arg()
 *  2016/09/23 kinoshita
 *  	modified commandline_get_arg()
 *  		when no argument exists, null string is returned (i.e. arg[0] == '\0')
 *  2016/10/24 kinoshita
 *  	collected command names and command functions together
 *  2016/11/09 kinoshita
 *  	rearranged the order of arguments in "commandline_get_arg"
 *
 */


#include "commandline.h"
#include <string.h>


static char cmd_arg[COMMANDLINE_NARG_MAX][COMMANDLINE_ARGLEN_MAX];
static int n_cmd_arg; // number of tokens in input string (includes command token)


// get command, and execute command function
// argument : command string (command argument should be separated by space character)
// return : true -> command execution succeeded
//          false -> illegal command, or empty string
bool commandline_input(char *cmd)
{
    char *token;
    int i;


    // separate command token
    token = strtok(cmd, " ");
    for(n_cmd_arg = 0; n_cmd_arg < 20; n_cmd_arg++){
        if(token == NULL)
            break;
        else{
            strcpy(cmd_arg[n_cmd_arg], token);
            token = strtok(NULL, " ");
        }
    }

    // compare first token and command names
    if(n_cmd_arg > 0){
        for(i = 0; i < n_commandline; i++){
            if( !strcmp(cmd_arg[0], commandline_sets[i].name)){
                //
                commandline_sets[i].func();
                break;
            }
        }
        if( i >= n_commandline )
            return false;
        else
        	return true;
    }
    else
    	return false;

}

// get command argument
// argument : 
//     iarg : argument position (0 -> command header)
//     arg : argument string (return data)
//     arglen : max length of "arg"
// return :
//		true : successfully got an argument
// 		false : iarg was out of range
bool commandline_get_arg(int iarg, char *arg, int arglen)
{
	if(iarg < n_cmd_arg){
		arg[arglen-1] = '\0'; // guarantee null termination
		strncpy(arg, cmd_arg[iarg], arglen-1);
		return true;
	}
	else{
		arg[0] = '\0';
		return false;
	}
}


// get number of arguments (including command token)
int commandline_narg(void)
{
	return n_cmd_arg;
}


