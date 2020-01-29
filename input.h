#ifndef SHELLY_INPUT_H
#define SHELLY_INPUT_H

#define BUF_SIZE 256

#include <sys/types.h>

/**
 * Asks for some input and returns the values from stdin.
 * Removes tailing newlines.
 * Adds lines to history.
 */
char *rl_gets(const char *s);

/**
 * Tokenize a line of text.
 * Supported delimiters: Space (' ') and Tab ('\t')
 * Escape character: Quote (")
 *
 * Return: A 2D array of tokens, each with variable width.
 */
char **tokenize(const char *line);

/**
 * Add a new string to an 2D array of strings at index i.
 * Dynamically grows the buffer.
 *
 * @param arr : 2D array of string to grow
 * @param token : the token to append
 * @param size : Reference to current buffer size
 * @param i : the current index
 *
 * @return the address of the 2D array
 */
void *tok_add(char **arr, char *token, int *size, int i);

#endif
