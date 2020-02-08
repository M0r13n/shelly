#include "input.h"
#include "parse.h"
#include <stdlib.h>

int main()
{
    /* Add some custom autocomplete functions */
    initialize_readline();

    char *line;

    while (1)
    {
        line = rl_gets(">>> ");
        execute_commands(line);
        free(line);
    }
    return 0;
}