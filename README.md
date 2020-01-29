```


  _____ _          _ _       
 / ____| |        | | |      
| (___ | |__   ___| | |_   _ 
 \___ \| '_ \ / _ \ | | | | |
 ____) | | | |  __/ | | |_| |
|_____/|_| |_|\___|_|_|\__, |
                        __/ |
                       |___/ 

``` 

# Shelly - A simple shell written in C
Shelly is a **very basic** shell that I wrote to teach myself more about C and POSIX processes.

# Features
- [x] Supports builtin commands `cd`, `help` and `exit`
- [x] Is able to launch processes
- [x] Supports whitespace escaping
- [x] History
- [x] Autocompletion (filenames and built in commands)
- [ ] Piping
- [ ] Redirection


# Compile
```sh
$ cmake . && make
```

# Usage
```sh
$ ./shelly
```


# How does it work?
The following is a small and incomplete writeup for me to consolidate what i've learned.

There are currently four different C files: **main.c**, **input.c**, **process.c**, and **utils.c**.

When the program is started, **main.c** is executed.

First of all `initialize_readline();` is called once.
This function is used to extend the default behaviour of readlines autocompletion.

Normally the GNU library readline ships with autocompletion for filenames.
This is very helpful, but not enough. I want Shelly to be able to autocomplete at least all of it's built in commands.
Therefore it is needed to set `rl_attempted_completion_function = (CPPFunction *) command_name_completion;` during
initialization. That function is located inside **input.c**. `command_name_completion` takes three arguments:

1. **text**: This text should be autocompleted
2. **START** and **END**: START and END show the region of text to complete.

This function checks if start is zero (assuming that only the first word can be a command).
If the former is true it searches through the builin commands and tries to find matching strings for autocompletion.
It uses readlines internal function `completion_matches`
that uses a generator function to generate the list of possible matches.
In this case the generator function `command_name_generator` is called repeatedly from `completion_matches`.
The single purpose of this method is to compare the partial text to all built in commands.
It takes the text and the current state (number of iterations so far) as arguments and always returns a string.
Text is the partial word to complete. When there are no possibilities left it returns `((char *) NULL);`.

**Note**: If `command_name_completion` is called for any other than the first word, it returns `(char **) NULL;`.
This enables fallback to filename completion built into readline.



