#include "input.h"
#include "utils.h"
#include "process.h"
#include <stdlib.h>

int main()
{
    char *line;
    char **args;
    int status = 1;

    while (status)
    {
        line = input(">>> ");
        args = tokenize(line);
        status = execute(args);

        free(line);
        free_2D(args);
    }
    return 0;
}