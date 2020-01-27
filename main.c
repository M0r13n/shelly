#include "input.h"
#include "utils.h"
#include "process.h"
#include <stdlib.h>

int main()
{
    char *line;
    char **args;
    int status = 1;

    print_2D(tokenize("echo Hello World"));
    print_2D(tokenize("echo \"Hello World\""));
    print_2D(tokenize("echo        \"Hello          World\"     "));
    print_2D(tokenize(""));
    print_2D(tokenize("\"\""));
    print_2D(tokenize("         "));
    print_2D(tokenize("echo 1          äöü "));
    print_2D(tokenize("\"touch index.html;"));
    print_2D(tokenize("\ttttttttt sdf \t"));
    print_2D(tokenize("cat text.xml | grep foo.bar"));

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