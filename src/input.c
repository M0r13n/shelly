#include "input.h"
#include "process.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <editline/readline.h>

static char *line_read = (char *) NULL;

/* The folder is stored and updated manually so that repeated access is fast.
 * Calling get_folder would be inefficient, because the full path needs to be traversed every time the method is called.
 */
static char FOLDER[PATH_MAX] = {-1};

int get_folder(char *buffer, int siz)
{
    /* Get current (full) path */
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
        return -1;
    }

    /* Search for last occurrence of a '/' (assumes that folder names are separated by '/') */
    char *pch;
    char *last = cwd;
    pch = strchr(cwd, '/');
    while (1)
    {
        pch = strchr(pch + 1, '/');
        if (pch == NULL)
        {
            break;
        }
        last = pch;
    }

    /* Copy the remaining part into buffer */
    strncpy(buffer, last + 1, siz);
    return 0;
}

void set_folder(char *name)
{
    if (strstr(name, ".."))
    {
        /* Replace relative folders like '..' or '../..' with the actual name */
        get_folder(FOLDER, PATH_MAX);
    }
    else
    {
        /* Copy the content */
        FOLDER[0] = '\0';
        strncat(FOLDER, name, PATH_MAX - 1);
    }
}

char *cur_folder()
{
    if (FOLDER[0] == -1)
    {
        /* Get current folder on first start */
        get_folder(FOLDER, PATH_MAX);
    }

    if (strlen(FOLDER) == 0)
    {
        /* This is home dir */
        strcpy(FOLDER, "~");
    }

    return FOLDER;
}

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