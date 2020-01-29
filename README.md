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
