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
- [x] Piping
- [x] Redirection


# Compile
#### Manually
```sh
$ mkdir -p ./build && cd ./build && cmake ..  && make ; cd .. ; 
```

#### Using build.sh
```sh
$ chmod +x ./build.sh && ./build.sh
```

# Run
After you build **shelly** you can can it:

```sh
$ ./build/shelly
```

# Examples

```sh
>>> ls -l | wc -c > somefile.out
```
```sh
>>> ls -l | grep shelly > somefile.out
```
```sh
>>> tail -2 somefile.out > somefile.out
```
```sh
>>> echo "Hello Over there" > somefile.out
```
```sh
>>> cat main.c | grep a > somefile.out
```
```sh
>>> curl -L google.com > google.html
```

# Memory leaks ?

```sh
➜  ~ leaks 36673         
Process:         shelly [36673]
Path:            /Users/USER/*/shelly
Load Address:    0x109943000
Identifier:      shelly
Version:         ???
Code Type:       X86-64
Parent Process:  zsh [1331]

Date/Time:       2020-02-09 13:06:38.209 +0100
Launch Time:     2020-02-09 13:05:12.482 +0100
OS Version:      Mac OS X 10.15.2 (19C57)
Report Version:  7
Analysis Tool:   /usr/bin/leaks

Physical footprint:         508K
Physical footprint (peak):  508K
----

leaks Report Version: 4.0
Process 36673: 279 nodes malloced for 184 KB
Process 36673: 0 leaks for 0 total leaked bytes.
```

# How does it work?
The following is a small and incomplete writeup for me to consolidate what i've learned.


### Autocompletion
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

### Pipes

A **pipe** is used to connect the standard input *stdin* of one process to the standard output *stdout* of another.
Pipes are used since early versions of UNIX. They are often used like this:

```sh
$ ls | sort | grep Music
```

The above chain of commands pipes the output of `ls` to `sort` and then from sort to `grep`.

**Some facts about pipes:**
- Pipes are unidirectional. A process can either write to or read to from a pipe, **but not both**.
This is called a *half duplex* pipe. If we want to create a bidirectional (*full duplex*) pipe, we need two pipes.sh
- Pipes can only be established between process with the same parents. Normally a pipe is created by calling `fork()` from a parent process.
Which leaves two processes (*parent* and *child*)


###### The `pipe` syscall
A pipe is created with the following syscall:

```C
#include <unistd. h.>
int pipe( int fd[2] );
```

The function returns `0` on success and `-1` on error.
Note that there are two file descriptors:

- `fd[0]` is used for reading from the pipe
- `fd[1]` is used for writing to the pipe

Having those file descriptors inside the same process is not terrible useful.
This way to process can send data to itself. Instead we fork after we created the pipe.
This way both processes have local copies of `fd[0]` and `fd[1]`. The only thing left to do,
is do signal which process should write and which process should read. This is done by closing the unused descriptor.

Parent process writes / child reads : Parent closes  `fd[0]` and child closes  `fd[1]`.

# Good Reads

- [GNU READLINE](http://web.mit.edu/gnu/doc/html/rlman_2.html)
- [Shelly Basics (Build your own shell)](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [Pipes](https://www.tldp.org/LDP/lpg/node11.html)
- [Pipes (german)](http://openbook.rheinwerk-verlag.de/linux_unix_programmierung/Kap09-002.htm)


