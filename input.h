#ifndef SHELLY_INPUT_H
#define SHELLY_INPUT_H

#define BUF_SIZE 256


/**
 * Tell the GNU Readline library how to complete.
 * Currently Shelly supports command completion for built in commands and filename completion.
 */
void initialize_readline();

/**
 * Attempt to complete on the contents of TEXT.
 * START and END show the region of text to complete.
 * Return the array of matches if any or NULL if None.
 */
char **command_name_completion(const char *text, int start, int end);

/**
 * Generator function for command completion.
 * TEXT is the text to complete.
 * STATE is the number of iterations so far (zero on first call).
 */
char *command_name_generator(const char *text, int state);

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
