#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"


char *builtin_str[] = {
        "cd",
        "help",
        "exit"
};

int (*builtin_func[])(char **) = {
        &_cd,
        &_help,
        &__exit
};

int builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}


int launch(char **args, int fd_in, int pipe_out)
{
    pid_t pid, w_pid;
    int status = 0;
    int fds[2];

    pipe(fds);
    pid = fork();
    if (pid == 0)
    {
        if (pipe_out)
        {
            dup2(fds[1], STDOUT_FILENO);
        }

        if (fd_in > 0)
        {
            dup2(fd_in, STDIN_FILENO);
        }

        /* Replace the current program with a new one */
        if (execvp(args[0], args) == -1)
        {
            perror("");
            exit(EXIT_FAILURE);
        }
        return 0;
    }

    else if (pid > 0)
    {
        /* Parent process */
        do
        {
            w_pid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    else
    {
        /* Fork failed */
        perror("Fork failed\n");
    }

    if (fd_in > 0)
        close(fd_in);

    close(fds[1]);

    if (!pipe_out)
        close(fds[0]);
    else
        return fds[0];

    return fds[0];
}


int _cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "cd needs an argument\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("lsh");
        }
    }
    return 1;
}

int _help(char **args)
{
    printf("    +---------------------------------------------------------------------+\n"
           "    |                                                                     |\n"
           "    |   _____ _          _ _                                              |  \n"
           "    |  / ____| |        | | |                                             |\n"
           "    | | (___ | |__   ___| | |_   _                                        |\n"
           "    |  \\___ \\| '_ \\ / _ \\ | | | | |                                       |\n"
           "    |  ____) | | | |  __/ | | |_| |                                       |\n"
           "    | |_____/|_| |_|\\___|_|_|\\__, |                                       |\n"
           "    |                         __/ | ©M0r13n                               |\n"
           "    |                        |___/                                        |\n"
           "    |                                                                     |\n"
           "    | A simple shell written in pure C.                                   |\n"
           "    +---------------------------------------------------------------------+\n");
    return 1;
}

int __exit(char **args)
{
    return 0;
}

int execute(char **args, int fd_in, int pipe_out)
{
    int i;

    if (args[0] == NULL)
    {
        /* No commands */
        return 1;
    }

    for (i = 0; i < builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }

    return launch(args, fd_in, pipe_out);
}
