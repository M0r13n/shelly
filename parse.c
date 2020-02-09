#include "process.h"
#include "parse.h"
#include <string.h>
#include <ctype.h>

/* Flags */
static int PIPE_IN;
static int PIPE_OUT;
static int REDIR;
const char specials[] = "|;&>";


/**
 * Reset all Flags.
 */
static void reset()
{
    PIPE_IN = 0;
    PIPE_OUT = 0;
    REDIR = 0;
}

/**
 * Increase the pointer while the current char is a space.
 */
static char *skipspace(char *s)
{
    while (isspace(*s)) ++s;
    return s;
}

/**
 * Check if a given char is reserved, e.g. has a special meaning.
 * Returns True if the char is reserved, else False.
 */
int isreserved(int c)
{
    if (c == '|' || c == ';' || c == '&' || c == '>')
    {
        return 1;
    }
    return 0;
}

/**
 * Split a line into single words separated by whitespaces.
 * Multiple whitespaces are omitted.
 *
 * The cmd string is altered. There are \0's inserted to terminate substrings of cmd.
 *
 * Args then stores pointers to positions in cmd. Each pointer points to the beginning of a word.
 *
 * Example:
 * -------------------------------------
 * Input:
 * A string (with whitespaces).
 * cmd = "ls -l"
 *
 * Output:
 * cmd = "ls\0   -l\0"
 *        ^      ^
 *        |      |
 * args= [p0,    p1]
 *
 */
static void split(char **args, char *cmd)
{
    /* Skip leading whitespaces (if any) */
    cmd = skipspace(cmd);
    /* From there on search for the next whitespace */
    char *next = strchr(cmd, ' ');
    int i = 0;

    while ((next != NULL) && (i < MAX_ARGS - 2))
    {
        /* Next points to the first found whitespace */
        next[0] = '\0';
        /* Store a pointer to the string starting after next */
        args[i++] = cmd;
        /* Skip any leading whitespaces */
        cmd = skipspace(next + 1);
        /* Find the next space */
        next = strchr(cmd, ' ');
    }
    /* Catch the last word */
    if (cmd[0] != '\0')
    {
        args[i++] = cmd;
    }
    /* Args is terminated with NULL */
    args[i] = NULL;
}

/**
 * Get the a sequence of connected chars.
 * Leading whitespaces are omitted.
 * Breaks as soon, as a space or a reserved character occurs.
 * Also removes the filename from line.
 *
 * Returns a copy of the filename.
 */
char *get_filename(char **line)
{
    /* Skip leading whitespaces */
    *line = skipspace(*line);
    /* Copy line */
    char *filename = strdup(*line);
    int i = 0;
    /* Search for the first special char or space */
    while ((filename[i] != '\0') && (!isreserved(filename[i])) && !(isspace(filename[i]))) ++i;
    /* Character @ pos i is not part of the filename */
    filename[i] = '\0';
    /* Remove the filename from line, so that the next command can be executed */
    *line = *line + i;
    return filename;
}

/**
 * Execute a single command.
 * Handles Redirects.
 * Next is a pointer to the current command-delimiter (e.g. >, |, ; or &)
 */
int run_command(char **line, char *next)
{
    static char *args[MAX_ARGS];
    char *command = *line;
    char *outfilename = NULL;
    if (REDIR)
    {
        /* Get the filename for redirects */
        REDIR = 0;
        *line = next + 1;
        outfilename = get_filename(line);
    }
    else
    {
        /* Move pointer upwards */
        *line = next + 1;
    }
    /* Split the line into single words separated by space */
    split(args, command);
    return execute(args, PIPE_IN, PIPE_OUT, outfilename) * (PIPE_OUT > 0);
}


/**
 * Check if the current command-delimiter is either a pipe or a redirect
 * */
void check_last(char *next)
{
    /* Check for pipe */
    PIPE_OUT = *next == '|';
    REDIR = *next == '>';
    *next = '\0';
}

/**
 * Extract and then execute multiple commands from a single line.
 */
int execute_commands(char *cmd)
{
    cmd = skipspace(cmd);
    /* strpbrk returns a pointer to the first occurrence of any of the special chars */
    char *next = strpbrk(cmd, specials);
    reset();

    /* If next is NULL there are no special chars left */
    while (next != NULL)
    {
        check_last(next);
        PIPE_IN = run_command(&cmd, next);
        next = strpbrk(cmd, specials);
    }
    /* The last command has no pipe */
    PIPE_OUT = 0;
    return run_command(&cmd, next);
}