#ifndef SHELLY_UTILS_H
#define SHELLY_UTILS_H

/**
 * Concat a list of strings to a single string and place a delimiter between each substring.
 */
char *str_list_cat(char **strings, char delimiter);

/**
 * Free a 2D array of strings
 */
void free_2D(char **arr);


/**
 * Print a two dim array of strings.
 */
void print_2D(char **tokens);

#endif
