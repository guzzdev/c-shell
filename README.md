# Shell Implementation in C

A custom Unix shell implementation built from scratch in C as part of the [CodeCrafters](https://codecrafters.io) challenge.

## Features

- **Built-in Commands**
  - `exit` - Terminate the shell
  - `echo` - Print text to stdout
  - `type` - Display command type information (builtin vs external)

- **External Command Execution**
  - PATH resolution for executable lookup
  - Process forking and execution via `fork()` and `execv()`
  - Child process management with `waitpid()`

- **Command Discovery**
  - Searches `$PATH` environment variable for executables
  - Validates file permissions before execution

## Technical Implementation

- Written in C23
- Uses POSIX system calls (`fork`, `execv`, `waitpid`)
- Implements custom PATH traversal algorithm
- Handles process lifecycle management

## Building & Running

```bash
./your_program.sh #Build and run the shell
```

She sells seashells by the seashore