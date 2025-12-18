# BUILTINS

## [echo](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/echo.html)
Prints its arguments to the standard output, separated by spaces and followed by a newline.

### Implementation
* **`-n` Flag**: If the first argument is `-n` (multiple instances are allowed, e.g., `-n -n`), the trailing newline is suppressed.
* **Arguments**: Iterates over the remaining arguments, printing them.
* **Return**: Always returns `0` (EXIT_SUCCESS).

## [cd](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html)
Changes the current working directory.

### Implementation
* **Without arguments**: Changes to the directory specified in the `$HOME` variable.
    * *Error*: If `$HOME` does not exist, an error is printed.
* **`-` Argument**: Changes to the previous directory stored in `$OLDPWD` and prints the path.
    * *Error*: If `$OLDPWD` does not exist, an error is printed.
* **Normal Path**: Attempts to change to the specified directory using `chdir()`.
* **Environment Update**:
    * Stores the current directory in `$OLDPWD` before changing.
    * Updates `$PWD` with the new directory (using `getcwd` to obtain the absolute path).
* **Errors**: Handles "too many arguments" and permission/existence failures with `perror`.

## [pwd](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/pwd.html)
Prints the absolute path of the current working directory.

### Implementation
* Attempts to read the `$PWD` variable from the environment.
* If it does not exist or is invalid, it uses `getcwd()` to obtain the system path.
* Prints the path followed by a newline.

## [export](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/export.html)
Adds or modifies environment variables.

### Implementation
* **Without arguments**: Prints all environment variables sorted alphabetically in the format `declare -x KEY="value"`.
* **With arguments (`KEY=value`)**:
    * Verifies that the `KEY` is a valid identifier (alphanumeric/underscore, does not start with a number).
    * If valid, it adds the variable to the environment or updates its value if it already exists.
* **Concatenation (`KEY+=value`)**:
    * If `+=` is detected, it looks for the current value of the variable and appends the new value to the end. If it did not exist, it creates it.
* **Errors**: If an identifier is invalid, it prints "not a valid identifier" and continues with the next argument (returns 1 at the end).

## [unset](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/unset.html)
Removes variables from the environment.

### Implementation
* Iterates through the list of arguments.
* Searches for each key in the environment variable linked list (`t_env`).
* If found, it frees the node memory and removes it from the list by relinking the pointers.
* Does nothing if the variable does not exist.

## [env](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/env.html)
Prints the current environment.

### Implementation
* Iterates through the list of environment variables.
* Prints only variables that have an assigned value (format `KEY=VALUE`).
* Ignores hidden or valueless variables (if any exist in the internal implementation).

## [exit](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/exit.html)
Terminates the shell execution.

### Implementation
* Always prints `exit` to `stderr`.
* **Without arguments**: Exits with the exit status of the last executed command.
* **With a numeric argument**:
    * Verifies that it is a valid number and does not overflow (`long long`).
    * Exits with the specified code (modulo 256).
* **Argument Errors**:
    * *Non-numeric*: Prints "numeric argument required" and exits with status `2` (Bash compliant).
    * *Too many arguments*: Prints "too many arguments" and **DOES NOT exit** (returns 1), keeping the interactive shell alive.
* Frees all memory before closing the process.
