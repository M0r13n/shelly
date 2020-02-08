#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "process.h"
#include "input.h"


char *builtin_str[] = {
        "cd",
        "help",
        "exit",
        "pwd"
};

int (*builtin_func[])(char **) = {
        &_cd,
        &_help,
        &__exit,
        &_pwd
};

int builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}


int launch(char **args, int fd_in, int pipe_out, char *outfilename)
{
    pid_t pid, w_pid;
    int status = 0;
    int fds[2];

    /* Create a pipe before forking, so that both the child/parent have access to it */
    pipe(fds);
    pid = fork();

    if (pid == 0)
    {
        /* Child process, e.g. the program to launch */
        if (pipe_out)
        {
            dup2(fds[1], STDOUT_FILENO);
        }

        if (fd_in > 0)
        {
            dup2(fd_in, STDIN_FILENO);
        }

        if (outfilename != NULL)
        {
            freopen(outfilename, "a+", stdout);
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
        /* Parent process needs to wait for all children to finish */
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

    /* If the input pipe is still open close it */
    if (fd_in > 0)
        close(fd_in);

    /* Close WRITE pipe */
    close(fds[1]);

    if (!pipe_out)
        close(fds[0]);

    /* Return the read pipe file descriptor*/
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
    /* Update the current folder */
    set_folder(args[1]);
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
    exit(0);
}


int _pwd(char **args)
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
        return 1;
    }
    else
    {
        perror("getcwd() error");
        return 0;
    }
}

int execute(char **args, int fd_in, int pipe_out, char *outfilename)
{
    int i;

    if (args[0] == NULL)
    {
        /* No commands */
        return 1;
    }

    /* Check if the program is builtin */
    for (i = 0; i < builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }

    /* Launch the program */
    return launch(args, fd_in, pipe_out, outfilename);
}
