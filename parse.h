#ifndef SHELLY_PARSE_H
#define SHELLY_PARSE_H

#define BUF_SIZE 256
#define MAX_ARGS  256

#define ERR_MAX_ARGS -11
#define ERR_MALLOC -2

int execute_commands(const char *line);

#endif
