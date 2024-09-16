# MiniShell
Our own fully functional Shell terminal
Efficiency is not guaranteed!


# Program Sequence
### 1. Program Start (main)

#### Initialization of Variables:

- Global variables such as g_signal are initialized to handle signals.
- The fill_struct() function is called to initialize the t_exec structure, which contains the shell environment in the form of a hash table, the abstract syntax tree (AST), and other control parameters.

#### Main Loop:
- The program enters a while (1) loop that repeats indefinitely, allowing the shell to continue running until the user decides to exit.
  
### 2. Environment and Terminal Configuration

#### Restoring and Configuring the Terminal:
- ft_restore_terminal(0) and ft_configure_terminal() are responsible for configuring the terminal for interactive input, ensuring that the settings are suitable for reading commands.
#### Waiting for Commands:
- The shell waits for the user to type a command. Typically, this is done by using readline to capture user input.

### 3. Command Parsing

#### Tokenization:
- The command entered by the user is parsed and broken down into tokens. Tokens are the meaningful parts of the command (such as words, operators, etc.).

#### AST Construction:

- An Abstract Syntax Tree (AST) is built from the tokens using the parser() function.
- This tree represents the logical structure of the command, allowing the identification of which part is a command, a redirection, a pipe, etc.

#### Error Checking:

- If there are syntax errors in the command, the shell will detect them and may display an error message or decide how to handle it. If the error occurs in a non-interactive environment, the shell may exit.

### 4. Command Execution

#### Node Type Determination:

- Depending on the type of node (command, redirection, logical operator such as AND or OR, etc.), the execution() function is responsible for executing the corresponding part of the tree.

#### Node Execution:

- The actual execution of the command(s) specified in the AST is performed. This may involve running a binary, handling redirections, executing conditional commands, handling pipes, etc.

#### Redirections and Pipes: 
- If the command involves redirections (> or <) or pipes (|), file descriptors are adjusted and subprocesses are created if necessary.

#### Signal Handling:
- During execution, signals (such as SIGINT for Ctrl+C or SIGQUIT for Ctrl+) are handled to allow controlled interruption or termination of commands.

### 5. Post-Execution

#### Releasing Resources:
- Once the command has been executed, the syntax tree (AST) is released using node_tree_delete(), preventing memory leaks.

#### Loop Restart:
- After execution and cleanup, the shell returns to the start of the loop, waiting for a new command from the user.

### 6. Shell Exit
#### Exit Command:
- If the user types an exit command, such as exit, or is in a non-interactive environment and finishes processing the input, the shell will call exit_shell() to exit cleanly.
- Final Cleanup: All remaining resources are freed and the shell ends its execution.
