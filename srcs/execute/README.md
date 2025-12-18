# EXECUTION MODULE

## Main Flow (`ft_exec_cmd_line`)
The main function coordinates the execution of a complete command line (pipeline).

### General Algorithm
1.  **Initialization**: Prepares the `t_values` structure with environment data and the command list.
2.  **Pipe Creation**: Calls `ft_set_pipes` to create all necessary pipes before forking (`pipe()`).
3.  **Parent Builtin Execution**:
    * If there is **only one command** and it is a **builtin** (e.g., `cd`, `export`, `exit`), it executes directly in the parent process so its changes (like changing directory) persist.
    * *Note*: Redirections for this case are handled temporarily, and `stdin`/`stdout` are restored upon completion.
4.  **Forking Loop**:
    * Iterates over each command in the list.
    * Configures command-specific redirections.
    * Calls `fork()` to create a child process.
    * **In the Child**:
        * Duplicates file descriptors (`dup2`) to connect input/output to pipes or files.
        * Closes unused pipes.
        * Executes the command (`execve`) or the builtin.
    * **In the Parent**:
        * Closes the ends of the pipes it no longer needs.
        * Advances to the next command.
5.  **Waiting (`ft_wait_children`)**: The parent waits for all children to finish (`waitpid`) and collects the exit status of the last command to update `$?`.

## Pipe Management
Inter-process communication is achieved via UNIX pipes.

* **Creation**: An array of `int *` is allocated where each element is a pipe (`fd[2]`).
* **Connection**:
    * `cmd[i]` writes to `pipe[i][1]`.
    * `cmd[i+1]` reads from `pipe[i][0]`.
* **Safe Closing**: It is critical to close all unused file descriptors in both the parent and children to avoid FD leaks and to prevent processes from hanging while waiting for data (EOF).

## Redirections
Before executing a command, its inputs and outputs are configured.

### Supported Types
* **`<` (Input)**: Opens the file in read-only mode (`O_RDONLY`). If it fails, the process aborts.
* **`>` (Output Truncate)**: Opens the file in write mode (`O_WRONLY | O_CREAT | O_TRUNC`).
* **`>>` (Output Append)**: Opens the file in write mode, appending to the end (`O_WRONLY | O_CREAT | O_APPEND`).
* **`<<` (Here_doc)**:
    * Reads standard input line by line until the delimiter is found.
    * Expands variables (`$VAR`) if the delimiter is not quoted.
    * Writes the content to a temporary pipe and uses the read end as `STDIN` for the command.

### Priority
Redirections take precedence over pipes. If a command has an input pipe and a `< file` redirection, it will read from the file.

## Command Search (`ft_find_command_path`)
If the command is not an absolute or relative path (does not start with `/` or `./`), the shell searches for its executable in the system.

### Implementation
1.  Retrieves the `$PATH` environment variable.
2.  Splits the `$PATH` value by `:` using `ft_split`.
3.  Iterates through each directory, testing if `directory/command` exists and is executable (`access(X_OK)`).
4.  If found, returns the full path.
5.  If not, returns a copy of the original command (so `execve` can attempt to execute it or fail with the correct error).

## Execution (`ft_exec_args`)
This is the final stage within the child process.

1.  **Verification**: Checks if the command is a directory or if it lacks permissions.
2.  **Environment Conversion**: Transforms the `t_env` linked list into a `char **` array compatible with `execve`.
3.  **System Call**: Executes `execve(path, args, env)`.
    * If successful, the current process is replaced by the new program.
    * If it fails, memory is freed, the corresponding error is printed (e.g., "command not found"), and it exits with the appropriate status (127 for not found, 126 for not executable).

## Cleanup and Signals
* **Runtime Signals**:
    * `SIGINT` (Ctrl+C): Interrupts child processes.
    * `SIGQUIT` (Ctrl+\): Terminates child processes with a core dump (or "Quit" message).
* **Memory**: Upon execution completion (or after a fatal error in the child), `terminator()` or cleanup functions are called to free structures, lists, and close FDs before `exit`.
