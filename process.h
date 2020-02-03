#ifndef SHELLY_PROCESS_H
#define SHELLY_PROCESS_H

/** BUILTIN COMMANDS */
extern char *builtin_str[];

extern int (*builtin_func[])(char **);

/**
 * Forks a process and saves the return value.
 * Accepts a list of arguments that are executed by the child.
 * Example: echo hello -> forks and calls echo with "hello" as an argument.
 */
int launch(char **args, int fd_in, int pipe_out);

int execute(char **args, int fd_in, int pipe_out);

int _cd(char **args);

int _help(char **args);

int __exit(char **args);

int builtins();


#endif