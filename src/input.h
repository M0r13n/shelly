#ifndef SHELLY_INPUT_H
#define SHELLY_INPUT_H

#define ANSI_BLUE "\x1b[34m"
#define ANSI_RESET "\x1b[0m"


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
 * Get the current folder.
 * Folders are tracked for better efficiency.
 */
char *cur_folder();

/**
 * Set the current folder.
 * Folders are tracked for better efficiency.
 */
void set_folder(char *name);

/**
 * Get the current folder name.
 * Writes content into buffer with siz checking.
 */
int get_folder(char *buffer, int siz);


#endif
