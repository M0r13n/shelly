#include "input.h"
#include "utils.h"
#include "process.h"
#include <stdlib.h>
#include <editline/readline.h>

int main()
{
    char *line;
    char **args;
    int status = 1;

    while (status)
    {
        line = readline(">>> ");
        add_history(line);

        args = tokenize(line);
        status = execute(args);

        free(line);
        free_2D(args);
    }
    return 0;
}