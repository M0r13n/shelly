#include "input.h"
#include "parse.h"
#include <stdlib.h>

int main()
{
    /* Add some custom autocomplete functions */
    initialize_readline();

    char *line;
    int status = 1;

    while (status)
    {
        line = rl_gets(">>> ");
        status = execute_commands(line);
        free(line);
    }
    return 0;
}