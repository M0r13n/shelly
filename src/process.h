#ifndef SHELLY_PROCESS_H
#define SHELLY_PROCESS_H

/** BUILTIN COMMANDS */
extern char *builtin_str[];

extern int (*builtin_func[])(char **);

/**
 * Forks a process and saves the return value.
 * Accepts a list of arguments that are executed by the child.
 * Example: echo hello -> forks and calls echo with "hello" as an argument.
 *
 * @param args: A list of commands, where args[0] is the program to call.
 * @param fd_in: If > 0 launch will open the file descriptor can pipe its content to STDIN.
 * @param pipe_out: If > 0 launch will open a pipe and write STDOUT to it.
 * @param outfilename: If not NULL launch will write STDOUT to outfilename
 *
 * @return: A file descriptor to be used by the next program as it's input
 */
int launch(char **args, int fd_in, int pipe_out, char *outfilename);

/**
 * Check if a command should call a builtin function  or open a program via launch.
 *
 * @param args:  A list of commands, where args[0] is the program to call.
 * @param fd_in: If > 0 launch will open the file descriptor can pipe its content to STDIN.
 * @param pipe_out: If > 0 launch will open a pipe and write STDOUT to it.
 * @param outfilename: If not NULL launch will write STDOUT to outfilename
 *
 * @return: A file descriptor to be used by the next program as it's input
 */
int execute(char **args, int fd_in, int pipe_out, char *outfilename);

/**
 * Builin method for changing directory.
 */
int _cd(char **args);

/**
 * Builtin method that displays some help text.
 */
int _help(char **args);

/**
 *  Builtin method that exits the shell.
 */
int __exit(char **args);

/**
 * Builtin method for getting the current dir.
 */
int _pwd();

int builtins();


#endif