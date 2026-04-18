# MyShell

A lightweight UNIX shell written in C, built to explore how command-line interpreters actually work at the system level.  
Instead of relying on high-level wrappers like `system()`, this shell uses low-level POSIX system calls such as `fork()`, `execvp()`, `wait()`, `signal()`, `open()`, and `dup2()` to manage processes, handle input/output, and replicate core shell behaviour.

---

## Overview

MyShell is an interactive command-line program that reads user input, parses commands, and executes them in a way similar to Bash. The goal of this project was to understand:

- How shells create and manage processes
- The distinction between built-in commands and external programs
- Signal handling and interrupt control
- File descriptor manipulation for I/O redirection
- Structuring a modular C project

---

## Features

### Core Shell
- Interactive prompt loop
- Reads input using `getline`
- Parses commands and arguments
- Executes programs and waits for completion
- Clean exit on `Ctrl+D` (EOF)

### Process Management
- Uses `fork()` to create child processes
- Uses `execvp()` to execute commands
- Parent process synchronises using `wait()`

### Timestamped Prompt
- Displays current date and time:
  ```
  [dd/mm hh:mm]#
  ```

### Signal Handling
- Handles `SIGINT` (`Ctrl+C`) without exiting the shell
- Mimics Bash behaviour by printing a fresh prompt

### Built-in Commands
- `cd` implemented as a shell built-in
  - Supports relative and absolute paths
  - Defaults to `$HOME` if no argument is given
  - Proper error handling via `perror()`

### Output Redirection
- Supports:
  ```
  command > file
  ```
- Redirects `stdout` using `open()` and `dup2()`

---

## Project Structure

```
.
├── src/
│   ├── main.c        # Entry point, shell loop
│   ├── input.c       # Input reading and parsing
│   ├── prompt.c      # Prompt formatting (timestamp)
│   ├── signals.c     # Signal handling (SIGINT)
│   ├── builtins.c    # Built-in commands (cd)
│   └── exec.c        # fork/exec logic + redirection
│
├── include/
│   ├── input.h
│   ├── prompt.h
│   ├── signals.h
│   ├── builtins.h
│   └── exec.h
│
├── Makefile
└── README.md
```

---

## Build & Run

### Compile
```bash
make
```

### Run
```bash
./my_shell
```

### Clean
```bash
make clean
```

---

## Example Usage

```bash
# ls
file1 file2 my_shell

# pwd
/home/user/project/

# echo hello world
hello world

# sleep 5

# ls > out.txt
```

---

## Key Concepts Demonstrated

- Process lifecycle (fork → exec → wait)
- Parsing input into `argv`-style arrays
- Signal handling with `SIGINT`
- File descriptor manipulation (`dup2`)
- Implementing shell built-ins vs external commands
- Modular C project design

---

## Why This Project

This project was built to move beyond using the shell and instead understand how it works internally. It ties together multiple core UNIX concepts and provides a solid foundation for systems programming, operating systems, and low-level software development.

---

## Author

David Neškrabal  
BSc Computer Science, University College Dublin
