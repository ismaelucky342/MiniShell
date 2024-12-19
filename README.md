# MINISHELL
![image](https://github.com/user-attachments/assets/74cdad66-ab91-4859-a986-552f75f73fc6)


## Description

Minishell is a group project with the objective of replicating a Unix shell that mimics Bash’s fundamental behavior. This project provides a hands-on approach to understanding how command interpretation, parsing, and execution are handled in real-world shells. It incorporates key functionalities such as command history, signal management, input/output redirections, and the parsing and execution of commands through, in our case, with an Abstract Syntax Tree (AST).
![image](https://github.com/user-attachments/assets/896c67a4-d867-4059-952a-5a93eaa50968)

## Collaborators

- [**Ismael Hernández Clemente:**](https://github.com/ismaelucky342)
- [**Daniel Gómez-Llusá:**](https://github.com/Danielaco23)

## Key Features

- **Interactive Command Prompt**: Displays a prompt, waits for user input, and processes commands.
- **Command History**: Maintains a functional history allowing users to navigate and execute previous commands.
- **Executable Search**: Identifies and runs executables from the system’s `PATH` or through provided relative and absolute paths.
- **Redirection Handling**: Supports input (`<`), output (`>`), append (`>>`), and heredoc (`<<`) redirections.
- **Variable Expansion**: Expands environment variables prefixed with `$`.
- **Quoting Mechanism**:
    - **Single quotes (`'`)**: Disable interpretation of all enclosed metacharacters.
    - **Double quotes (`"`)**: Disable interpretation except for the `$` symbol for variable expansion.
- **Signal Handling**: Manages signals effectively without relying on global variables, ensuring modular and maintainable code.
- **AST Construction and Parsing**: Uses an Abstract Syntax Tree to parse and execute complex command structures.

## Replicating Bash

Minishell strives to replicate essential features of Bash, adhering to its syntax and command behavior. While it is not a full Bash implementation, Minishell includes the core aspects that are necessary for typical command-line usage:

- **Execution Behavior**: Commands are processed similarly to Bash, with support for built-in commands and external executables.
- **Pipes and Redirections**: Minishell correctly interprets and executes pipes (`|`) and redirections, allowing for command chaining and output management.
- **Environment Variables**: Supports basic variable expansion and environmental variable access as Bash does.
- **Error Handling**: Implements basic error reporting to inform users of invalid commands or issues with execution.

However, due to the educational nature of the project, advanced Bash features such as job control, process substitution, and complex shell scripting are beyond its scope.

## Abstract Syntax Tree (AST)

An Abstract Syntax Tree (AST) is a tree representation of the abstract syntactic structure of code or commands. In Minishell, the AST is central to parsing and executing commands efficiently. Each node in the tree represents a command, redirection, or a control structure such as a pipe.

### How the AST Works

1. **Parsing Input**: The input command line is parsed into tokens, distinguishing between commands, arguments, operators, and special symbols.
2. **Building the AST**: Tokens are structured into an AST, where each node represents a logical component of the command. For instance, a pipe operator (`|`) splits commands into left and right subtrees.
3. **Execution**: The tree is traversed recursively, executing commands based on their position and relationship in the tree.

### Advantages of Using an AST

- **Structured Parsing**: Simplifies parsing by breaking down complex commands into manageable subunits.
- **Execution Order**: Ensures commands are executed in the correct order, supporting nested and complex command combinations.
- **Error Management**: Provides a clear structure for handling syntax errors during parsing.

### Example Structure

An input like:

```
echo "hello" | grep "h" > output.txt
```

would be parsed into an AST with:

- A root node representing the pipe (`|`).
- The left child node representing `echo "hello"`.
- The right child node representing the redirection (`>`), with `grep "h"` as its subnode and `output.txt` as the output target.

## Project Requirements

### Allowed Functions

Minishell can use the following system functions, aligning with project constraints:

- `readline`, `add_history`, `malloc`, `free`, `write`, `fork`, `execve`, `pipe`, `dup2`, `open`, `close`, `wait`, `kill`, `getcwd`, `chdir`, `isatty`, among others.

### Libraries

- **libft**: The custom library `libft` can be used for utility functions.

## Project Structure

- **`src/`**: Source code files, including parsing, execution, and utility functions.
- **`include/`**: Header files defining structures and function prototypes.
- **`Makefile`**: For compilation and dependency management.

## Compilation and Execution

To compile Minishell, run:

```
make
```

This will create an executable named `minishell`. To run it:

```
./minishell
```

## Usage

Minishell supports basic shell operations such as:

- **Executing commands**: Run system commands and custom-built commands.
- **Command chaining**: Use pipes (`|`) to chain commands and redirections for output/input management.
- **Environment variable expansion**: Utilize variables prefixed with `$`.
- **Quoting**: Use single or double quotes for strings.

## Extras

Developing Minishell has been an extensive learning experience, emphasizing in gaining practical knowledge of `fork`, `execve`, and process management. Ensuring efficient use of `malloc` and `free` to avoid memory leaks. Creating reusable and maintainable code by adhering to project constraints (e.g., 1 global variable allowed) and implementing an AST to handle complex command syntax efficiently. The project provided invaluable insights into how shells work under the hood, enhancing our understanding of operating systems, process management, and command-line interfaces.

-Born2code
![42madrid](https://github.com/ismaelucky342/Born2code/assets/153450550/3a377f34-9156-4eff-b04b-71c4b128523e)
