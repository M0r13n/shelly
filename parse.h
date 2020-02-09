#ifndef SHELLY_PARSE_H
#define SHELLY_PARSE_H

#define MAX_ARGS  512

/**
 * Execute a line of commands.
 * Commands may be chained or a single line.
 * Commands are split into sub-commands while parsing.
 *
 * Supported chaining operator are: &, ;
 * Supports Piping with |
 *
 * Does not currently supports redirects.
 *
 */
int execute_commands(char *cmd);

#endif
