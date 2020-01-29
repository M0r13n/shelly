#include "input.h"
#include <stdlib.h>
#include <string.h>


void *tok_add(char **arr, char *token, int *size, int i)
{
    arr[i++] = strdup(token);
    /* Grow buffer if needed */
    if (i >= *size)
    {
        *size = *size + BUF_SIZE;
        arr = realloc(arr, *size * sizeof(char *));
        if (arr == NULL)
        {
            /* FATAL ERROR */
            exit(-1);
        }
    }
    return arr;
}


char **tokenize(const char *line)
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
    char **tokens = malloc(tokens_buf_size * sizeof(char *));
    if (tokens == NULL || token == NULL)
    {
        return NULL;
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
                tokens = tok_add(tokens, token, &tokens_buf_size, tot_tok_num++);

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
                return NULL;
            }
        }
    }
    if (tok_pos)
    {
        /* Copy the last token if it exists */
        token[tok_pos] = '\0';
        tokens = tok_add(tokens, token, &tokens_buf_size, tot_tok_num++);
    }
    tokens[tot_tok_num] = NULL;
    return tokens;
}