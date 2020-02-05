#include "process.h"
#include "parse.h"
#include <stdlib.h>
#include <string.h>

/* Flags */
static int PIPE_IN;
static int PIPE_OUT;
const char specials[] = "|;&";

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
 * Execute a single command
 */
int run_command(const char *line)
{
    char *args[MAX_ARGS];
    tokenize(args, line);
    return execute(args, PIPE_IN, PIPE_OUT);
}

/**
 * Reset all Flags.
 */
static void reset()
{
    PIPE_IN = 0;
    PIPE_OUT = 0;
}

/**
 * Execute multiple commands from a single line.
 */
int execute_commands(const char *line)
{
    char *cur = strdup(line);
    char *next = strpbrk(cur, specials);
    reset();

    while (next != NULL)
    {
        PIPE_OUT = *next == '|';
        *next = '\0';
        PIPE_IN = run_command(cur);
        if (!PIPE_OUT)
        {
            PIPE_IN = 0;
        }
        cur = next + 1;
        next = strpbrk(cur, specials);
    }
    PIPE_OUT = 0;
    return run_command(cur);
}