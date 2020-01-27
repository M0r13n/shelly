#ifndef SHELLY_INPUT_H
#define SHELLY_INPUT_H

#define BUF_SIZE 2

#include <sys/types.h>

/**
 * Copy of Python's input() method.
 * Asks for some input and returns the values from stdin.
 * Removes tailing newlines.
 */
char *input(const char *q);

/**
 * Tokenize a line of text.
 * Supported delimiters: Space (' ') and Tab ('\t')
 * Escape character: Quote (")
 *
 * Return: A 2D array of tokens, each with variable width.
 */
char **tokenize(const char *line);

#endif
