#ifndef SHELLY_PROCESS_H
#define SHELLY_PROCESS_H

/**
 * Forks a process and saves the return value.
 * Accepts a list of arguments that are executed by the child.
 * Example: echo hello -> forks and calls echo with "hello" as an argument.
 */
int launch(char **args);

int execute(char **args);

int _cd(char **args);

int _help(char **args);

int __exit(char **args);

int builtins();


#endif