#include "input.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char *input(const char *q)
{
    int chars;
    char *line = NULL;
    size_t buf_size = 0;

    printf("%s", q);
    chars = getline(&line, &buf_size, stdin);
    if (chars == -1)
    {
        return "";
    }
    /* Remove tailing newlines */
    if ((line)[chars - 1] == '\n')
    {
        (line)[chars - 1] = '\0';
    }
    return strdup(line);
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
                tokens[tot_tok_num++] = strdup(token);
                if (tot_tok_num >= tokens_buf_size - 1)
                {
                    tokens_buf_size += BUF_SIZE;
                    tokens = realloc(tokens, tokens_buf_size * sizeof(char *));
                    if (tokens == NULL)
                    {
                        return NULL;
                    }
                }
                /* Reset the token vars and allocate new space */
                tok_pos = 0;
                token[tok_pos] = '\0';
                token_buf_siz = BUF_SIZE;
            }
            continue;
        }

        /* Enter or leave escape mode */
        escaped = (cur_chr == '\"') ? 1 - escaped : escaped;

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
        tokens[tot_tok_num++] = strdup(token);
    }
    tokens[tot_tok_num] = NULL;
    return tokens;
}