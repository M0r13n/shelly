#include "input.h"
#include "process.h"
#include <stdlib.h>
#include <string.h>
#include <editline/readline.h>

static char *line_read = (char *) NULL;

void initialize_readline()
{
    /* Allow conditional parsing of the ~/.inputrc file. */
    rl_readline_name = "FileMan";

    /* Tell the completer that we want a crack first. */
    rl_attempted_completion_function = (CPPFunction *) command_name_completion;
}


char **command_name_completion(const char *text, int start, int end)
{
    char **matches;

    matches = (char **) NULL;

    /* Only the first word can be a command */
    if (start == 0)
        matches = completion_matches(text, command_name_generator);

    return (matches);
}

char *command_name_generator(const char *text, int state)
{
    static int list_index, len;
    char *name;

    /* Init */
    if (!state)
    {
        list_index = 0;
        len = (int) strlen(text);
    }

    /* Return the next name which partially matches from the command list. */
    name = builtin_str[list_index];
    while (name)
    {
        list_index++;

        if (strncmp(name, text, len) == 0)
            return (strdup(name));
        name = builtin_str[list_index];
    }

    /* If no names matched, then return NULL. */
    return ((char *) NULL);
}

char *rl_gets(const char *s)
{
    /* Free allocated buffer if it exists */
    if (line_read)
    {
        free(line_read);
        line_read = (char *) NULL;
    }

    /* Ask for input */
    line_read = readline(s);

    /* Save non empty lines */
    if (line_read && *line_read)
        add_history(line_read);

    return strdup(line_read);
}

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