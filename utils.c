#include "input.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char *str_list_cat(char **strings, char delimiter)
{
    int buf_size = BUF_SIZE;
    int cur = 0;
    int pos;
    int total = 0;
    char cur_chr;
    char *str;
    char *string = malloc(buf_size * sizeof(char));

    /* Memory error */
    if (string == NULL)
    {
        return NULL;
    }

    /* Iterate over string char by char */
    while ((str = strings[cur++]) != NULL)
    {
        pos = 0;
        while (1)
        {
            cur_chr = str[pos++];
            /* Place the delimiter between the strings*/
            if (cur_chr == '\0')
            {
                string[total++] = delimiter;
                break;
            }

            /* Store the current char */
            string[total++] = cur_chr;
            if (total >= buf_size)
            {
                buf_size += BUF_SIZE;
                string = realloc(string, buf_size * sizeof(char));
                if (string == NULL)
                {
                    return NULL;
                }
            }
        }
    }
    /* Override the previous char to remove a tailing delimiter. */
    string[--total] = '\0';
    return string;
}

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


void print_2D(char **tokens)
{
    printf("%s\n", str_list_cat(tokens, ','));
}
