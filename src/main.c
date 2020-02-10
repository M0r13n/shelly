#include "input.h"
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    /* Add some custom autocomplete functions */
    initialize_readline();

    char *line;

    while (1)
    {
        printf("%s(%s)%s", ANSI_BLUE, cur_folder(), ANSI_RESET);
        line = rl_gets(">>> ");
        execute_commands(line);
        free(line);
    }
    return 0;
}

