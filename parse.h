#ifndef SHELLY_PARSE_H
#define SHELLY_PARSE_H

#define BUF_SIZE 256
#define MAX_ARGS  256

#define ERR_MAX_ARGS -11
#define ERR_MALLOC -2

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
int execute_commands(const char *line);

#endif
