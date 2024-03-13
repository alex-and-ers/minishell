# Project Overview

Minishell is designed to mimic the functionality of traditional Unix shells, providing a platform for executing commands and managing processes.
This project is an opportunity to understand the core functionalities of a shell, including parsing commands, handling environment variables, and implementing built-in functions.
# Features
    Command Execution: Minishell allows:
    The execution of commands either by using the PATH variable or by specifying relative or absolute paths.
    History Management: Maintains a history of executed commands, enabling easy recall and execution.
    Signal Handling: Properly handles signals like ctrl-C, ctrl-D, and ctrl-\, mirroring the behavior found in bash.
    Redirections and Pipes: Supports input and output redirections (<, >, <<, >>) as well as piping between commands (|).
    Environment Variables: Allows the use of environment variables with expansion of their values.
    Exit Status: Handles $?, expanding to the exit status of the most recently executed foreground pipeline.
    Built-ins: Implements several built-in commands such as echo, cd, pwd, export, unset, env, and exit.
