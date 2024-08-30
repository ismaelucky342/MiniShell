#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>
# include <termios.h>
# define DEBUG 0

// Colors
# define RED_INCIDATOR "\002\001\e[1m\e[31m●\e[0m\002"
# define MAGENTA_INCIDATOR "\002\001\e[1m\e[35m●\e[0m\002"
# define RESET "\e[0m\002"
# define RED "\002\001\e[1m\e[31m"
# define GREEN "\002\001\e[1m\e[32m"
# define YELLOW "\002\001\e[1m\e[33m"
# define BLUE "\002\001\e[34m"
# define MAGENTA "\002\001\e[1m\e[35m"
# define CYAN "\002\001\e[1m\e[36m"
// # define BACKGROUND "\033[48;5;93m"

typedef enum e_token_type
{
	T_WORD,
	T_SEPARATOR,
	T_PIPE,
	T_AND,
	T_OR,
	T_LPAREN,
	T_RPAREN,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_REDIR_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				quote;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef enum e_node_type
{
	ERROR,
	REDIR,
	AND,
	OR,
	PIPE,
	CMD,
}	t_node_type;

typedef struct s_cmd
{
	char	**args;
	char	**redirects;
	int		*redirect_type;
}	t_cmd;

typedef struct s_ast_node
{
	t_node_type		type;
	void			*value; // Puede ser un comando, redirección, etc.
	struct s_ast_node **children; // Array de punteros a hijos
	int				children_count; // Número de hijos
}	t_ast_node;

typedef struct s_exec
{
    t_hashtable *env_hashtable;  
    t_ast_node *tree;
    t_node_type type;
    int sub_process;
    int exit_status;
} t_exec;

//colors
char *color_string(char *str, char *color); 

// Parser functions
int				check_quotes(char *command);
char			*check_unclosed(char *command, t_exec *exec);
t_node_type		split_by_operator(t_token *token_last, t_ast_node **head);
t_node_type		tokens_to_tree(t_token *tokens, t_ast_node **head);
t_ast_node		*new_node(void);
t_ast_node		*new_redir_node(void);
t_token			*delete_parens(t_token *token_first);

// Pipeline functions
int				count_words(t_token *tokens);
t_token			*get_pipe(t_token *tokens);
t_token			*get_operator(t_token *tokens);

// Redirect functions
int				redirects_get(t_token **token_first, t_cmd **redirects);
int				climb_tree(t_ast_node *node, t_node_type type);

// Cleanup functions
t_node_type		err_pars(char *message, t_cmd *redirects, t_token **tokens);
void			print_syntax_err(t_token *token);
void			free_str_array(char **arr);
void			cmd_free(t_cmd *cmd);
void			node_tree_delete(t_ast_node *node, t_node_type type);
void			free_env(char ***env);

// Debug functions
void			debug_print_token_array(t_token *token_first);
void			get_next_debug(t_ast_node *node, t_node_type type, int i);

// Is_checks functions
int				is_quote(char c);
int				is_separator(char c);
int				is_redirect(t_token_type type);
int				is_operator(t_token_type type);
int				is_variable(char c);

// Tokenizer functions
t_token_type	t_type_process(char *string);
t_token			*next_token(char *string, t_token *token_last);
void			token_delete(t_token **tokens);
void			token_delete_all(t_token **tokens);
t_token			*token_add(t_token *tokens, t_token_type token_type);
t_token			*token_split(t_token *tokens, int direction);
t_token			*skip_parens(t_token *tokens, int direction);

// Command execution functions
t_node_type		parser(t_ast_node **token_tree, t_exec *exec);
char			*get_env(char **environ, char *var);
void			execution(t_ast_node *tree, t_node_type type, t_exec *exec);
int				exit_shell(t_exec *exec, char **arg, int status);

// Variable expansion functions
char			*expand_tilde(char *arg, char **env);
char			*expand_variables(char *command, t_exec *exec);
char			*expander(char *arg);
char			**expander_array(char **args, t_exec *exec);
int				heredoc_expand(int heredoc, t_exec *exec);
char			**word_splitting(char **args);

// Signal handling functions
void			parser_handler(int signal);
void			execution_handler(int signal);
void			ft_restore_terminal(int i);
void			ft_configure_terminal(void);

#endif
