#include "input.h"
#include "process.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char **args = NULL;
static int FD_IN;
static int PIPE_OUT;

void free_2D(char **arr)
{
    char *s;
    int cur = 0;
    while ((s = arr[cur++]) != NULL)
    {
        free(s);
    }
    free(arr);
}

void tok_add(char *token, int *size, int i)
{
    args[i++] = strdup(token);
    /* Grow buffer if needed */
    if (i >= *size)
    {
        *size = *size + BUF_SIZE;
        args = realloc(args, *size * sizeof(char *));
        if (args == NULL)
        {
            /* FATAL ERROR */
            exit(-1);
        }
    }
}


void tokenize(const char *line)
{
    /* Buffer sizes for both the current token and the list of tokens */
    int token_buf_siz = BUF_SIZE;
    int tokens_buf_size = BUF_SIZE;

    /* Variables for iterating over line */
    char cur_chr;

    int cur = 0, escaped = 0;
    /* Number of chars in current token */
    int tok_pos = 0;

    /* Total number of token */
    int tot_tok_num = 0;

    /* Buffers */
    char *token = malloc(token_buf_siz);
    args = malloc(tokens_buf_size * sizeof(char *));
    if (args == NULL || token == NULL)
    {
        exit(-1);
    }

    /* Iterate over line char by char */
    while ((cur_chr = line[cur++]) != '\0')
    {
        /* Check for unescaped delimiters */
        if ((cur_chr == ' ' || cur_chr == '\t') && !escaped)
        {
            /* Skip duplicate delimiters */
            if (tok_pos > 0)
            {
                /* Store the token and grow buffer if necessary */
                token[tok_pos] = '\0';
                tok_add(token, &tokens_buf_size, tot_tok_num++);

                /* Reset the token vars and allocate new space */
                tok_pos = 0;
                token[tok_pos] = '\0';
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
        token[tok_pos++] = cur_chr;
        if (tok_pos >= token_buf_siz)
        {
            token_buf_siz += BUF_SIZE;
            token = realloc(token, token_buf_siz * sizeof(char));
            if (token == NULL)
            {
                exit(-1);
            }
        }
    }
    if (tok_pos)
    {
        /* Copy the last token if it exists */
        token[tok_pos] = '\0';
        tok_add(token, &tokens_buf_size, tot_tok_num++);
    }
    args[tot_tok_num] = NULL;
}

int run_command(const char *line)
{
    tokenize(line);
    int r = execute(args, FD_IN, PIPE_OUT);
    free_2D(args);
    return r;
}

static void reset()
{
    FD_IN = 0;
    PIPE_OUT = 0;
}

int execute_commands(const char *line)
{
    const char specials[] = "|;&";
    char *cur = strdup(line);
    char *next = strpbrk(cur, specials);
    reset();

    while (next != NULL)
    {
        PIPE_OUT = *next == '|';
        *next = '\0';
        FD_IN = run_command(cur);
        if (!PIPE_OUT)
        {
            FD_IN = 0;
        }
        cur = next + 1;
        next = strpbrk(cur, specials);
    }
    PIPE_OUT = 0;
    return run_command(cur);
}