#include "process.h"
#include "parse.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Flags */
static int PIPE_IN;
static int PIPE_OUT;
static int REDIR;
const char specials[] = "|;&>";

/**
 * Adds a token into a 2D array.
 * Bounds are checked.
 */
void tok_add(char **args, char *token, int i)
{
    if (i > MAX_ARGS)
    {
        exit(ERR_MAX_ARGS);
    }
    if (token == NULL)
    {
        args[i] = NULL;
        return;
    }
    args[i] = strdup(token);
}

/**
 * Wrapper around malloc, that exits the program if malloc fails.
 */
void *malloc_safe(void *ptr, size_t siz)
{
    ptr = malloc(siz);
    if (ptr == NULL)
    {
        exit(ERR_MALLOC);
    }
    return ptr;
}


/**
 * Wrapper around realloc, that exits the program if realloc fails.
 */
void *realloc_safe(void *ptr, size_t siz)
{
    ptr = realloc(ptr, siz);
    if (ptr == NULL)
    {
        exit(-1);
    }
    return ptr;
}

/**
 * Tokenizes a string.
 * Splits the string into tokens separated by single space.
 */
void tokenize(char **args, const char *line)
{
    /* Buffer sizes for both the current token and the list of tokens */
    int token_buf_siz = BUF_SIZE;

    /* Variables for iterating over line */
    int cur_chr = 0, cur = 0, escaped = 0;

    /* Number of chars in current token */
    int tok_pos = 0;

    /* Total number of token */
    int tot_tok_num = 0;

    /* Buffers */
    char *token = malloc_safe(&token, token_buf_siz);

    /* Iterate over line char by char */
    while ((cur_chr = line[cur++]) != '\0')
    {
        /* Check for unescaped delimiters */
        if ((cur_chr == ' ' || cur_chr == '\t') && !escaped)
        {
            /* Skip duplicate delimiters */
            if (tok_pos > 0)
            {
                /* Store the token */
                token[tok_pos] = '\0';
                tok_add(args, token, tot_tok_num++);

                /* Reset the token vars and allocate new space */
                tok_pos = 0;
                token_buf_siz = BUF_SIZE;
            }
            continue;
        }

        /* Enter or leave escape mode */
        if (cur_chr == '\"')
        {
            escaped = 1 - escaped;
            continue;
        }

        /* Store the char and grow buffer if necessary */
        token[tok_pos++] = (char) cur_chr;
        if (tok_pos >= token_buf_siz)
        {
            token_buf_siz += BUF_SIZE;
            token = realloc_safe(token, token_buf_siz);
        }
    }
    if (tok_pos)
    {
        /* Copy the last token if it exists */
        token[tok_pos] = '\0';
        tok_add(args, token, tot_tok_num++);
    }
    tok_add(args, NULL, tot_tok_num);
}

/**
 * Reset all Flags.
 */
static void reset()
{
    PIPE_IN = 0;
    PIPE_OUT = 0;
    REDIR = 0;
}

/**
 * Increase the pointer while the current char is a space.
 */
static char *skipspace(char *s)
{
    while (isspace(*s)) ++s;
    return s;
}

/**
 * Check if a given char is reserved, e.g. has a special meaning.
 * Returns True if the char is reserved, else False.
 */
int isreserved(int c)
{
    if (c == '|' || c == ';' || c == '&' || c == '>')
    {
        return 1;
    }
    return 0;
}

/**
 * Get the a sequence of connected chars.
 * Leading whitespaces are omitted.
 * Breaks as soon, as a space or a reserved character occurs.
 * Also removes the filename from line.
 *
 * Returns a copy of the filename.
 */
char *get_filename(char **line)
{
    /* Skip leading whitespaces */
    *line = skipspace(*line);
    /* Copy line */
    char *filename = strdup(*line);
    int i = 0;
    /* Search for the first special char or space */
    while ((filename[i] != '\0') && (!isreserved(filename[i])) && !(isspace(filename[i]))) ++i;
    /* Character @ pos i is not part of the filename */
    filename[i] = '\0';
    /* Remove the filename from line, so that the next command can be executed */
    *line = *line + i;
    return filename;
}

/**
 * Execute a single command.
 * Handles Redirects.
 * Next is a pointer to the current command-delimiter (e.g. >, |, ; or &)
 */
int run_command(char **line, char *next)
{
    char *args[MAX_ARGS];
    char *command = *line;
    char *outfilename = NULL;

    if (REDIR)
    {
        /* Get the filename for redirects */
        REDIR = 0;
        *line = next + 1;
        outfilename = get_filename(line);
    }
    else
    {
        /* Move pointer upwards */
        *line = next + 1;
    }
    /* Split the line into single words */
    tokenize(args, command);
    return execute(args, PIPE_IN, PIPE_OUT, outfilename) * (PIPE_OUT > 0);
}


/**
 * Check if the current command-delimiter is either a pipe or a redirect
 * */
void check_last(char *next)
{
    /* Check for pipe */
    PIPE_OUT = *next == '|';
    REDIR = *next == '>';
    *next = '\0';
}

/**
 * Extract and then execute multiple commands from a single line.
 */
int execute_commands(const char *line)
{
    char *cur = strdup(line);
    /* strpbrk returns a pointer to the first occurrence of any of the special chars */
    char *next = strpbrk(cur, specials);
    reset();

    /* If next is NULL there are no special chars left */
    while (next != NULL)
    {
        check_last(next);
        PIPE_IN = run_command(&cur, next);
        next = strpbrk(cur, specials);
    }
    /* The last command has no pipe */
    PIPE_OUT = 0;
    return run_command(&cur, next);
}