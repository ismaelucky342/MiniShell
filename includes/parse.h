#ifndef PARSE_H
# define PARSE_H

# include "../Libft/libft.h"
# include "minishell.h"
# include <stdio.h>
# include <dirent.h>
# include <termios.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>

typedef struct s_token
{
	char	*str;
	int		type;
}	t_token;

typedef struct s_redirection_token
{
	char	*name;
	char	type;
}	t_redirection_token;

typedef struct s_tree_node
{
	char				**args;
	char				pipe_out;
	t_list				*redir_list;
	struct s_tree_node	*next;
	int					pid;
	int					exit;
	char				is_builtin;
	int					pipe_fds[2];
	char				*path;
}	t_tree_node;

typedef struct s_ast_tree
{
	struct s_ast_tree	*left;
	struct s_ast_tree	*right;
	t_list				*cmd_tokens;
	char				*cmd_str;
	char				*expanded_str;
	t_tree_node			*cmd_list;
	char				is_logic;
	int					exit;
}	t_ast_tree;

typedef struct s_minishell
{
	int			history_fd;
	int			last_exit;
	t_ast_tree	*cmd_tree;
	char		**envp;
	long		env_size;
	long		env_elems;
	char		*ft_prompt;
	char		eof;
	char		cont;
}	t_minishell;

void        ft_free_list(t_tree_node *cmd_list);
void        ft_free_redirections(void *t);

int			ft_fill_list(t_list *begin, t_ast_tree *tree_node);
void		*ft_free_ast_tree(t_ast_tree *tree);
char		*dictionary(char *str, int needle_tip);
int			ft_env_build(t_minishell *sack, char *key_val);
char		*get_value_from_env(char **envp, char *key, int *exists);
int			ft_remove_env(t_minishell *sack, char *key);
void		ft_env_no_value(t_minishell *sack);

int			ft_heredoc(char **str, int *i, char **f_name);
int			ft_expand_heredoc(int o_fd, t_redirection_token *tok, char **envp);
void		new_string(char **str, int j, char *tmp, char *tmp2);
void		heredoc_input(char **line, char *prompt, char *delim, int *fd);
char		*get_tmp_filename(void);

void		ft_init_file(t_minishell *sack);
void		ft_h_fill(t_minishell *sack);
void		ft_add_history(char *str, t_minishell *sack);

void		init_minishell(t_minishell *sack, char **envp, int argc, char **argv);
char		*ft_prompt(char **env);
t_list		*tokenizer(char	*str);
char		ft_is_reserved_char(char c);
void		ft_set_signal_handlers(void);
void		ft_sig_handler(int signum);

void		skip_to_delimiter(char *str, int *i, char delim);
void		skip_spaces(char *str, int *i, int *start, int mode);
int			ft_remove_quotes(t_list *tokens);
int			ft_exec_and_wait(t_ast_tree *tree_node, t_minishell *sack);
void		ft_str_unquote(char *str);



int			retokenize(t_list *curr, int type, int start, int *lngths);


char		*ft_wildcards(char *regex);
void        wildcard_expand(t_list *curr, int *i);
void		handle_wildcard(int *conts, char *f_name, char*regex);
int			strlen_and_free(char **tmp, char **tmp2, char **file);
void		get_files(DIR **dir_ptr, struct dirent **directory);
int			regex_iterator(char *regex, char *f_name, int *j, int i);
int         strlen_and_free(char **tmp, char **tmp2, char **file);

#endif