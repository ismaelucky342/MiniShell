/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:16:35 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 14:58:05 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*===============================INCLUDES AREA==============================*/

# include "../Libft/libft.h"
# include "structs.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>

/*===============================FUNCTIONS AREA==============================*/

//añade comentarios encima dee cada funcion /**/
/*---------------------------------AST_TREE----------------------------------*/

int			ft_ast_tree(t_list *begin, t_ast_tree *tree_node);
void		*ft_free_cmdtree(t_ast_tree *tree);


/*---------------------------------ENVIRONMENT-------------------------------*/

char		*ft_get_from_env(char **envp, char *key, int *exists);
int			ft_add_to_env(t_minishell *boogeyman, char *passkey);
char		*get_val_from_env(char **envp, char *key, int *exists);
int			ft_remove_env(t_minishell *boogeyman, char *key);
void		ft_remove_env_variables(t_minishell *boogeyman);

/*---------------------------------HEREDOC-----------------------------------*/

int			ft_heredoc(char **str, int *i, char **f_name);
char		*tmp_filename(void);
int			ft_expand_str_heredoc(int o_fd, t_redirection_token *tok, char **envp);
void		delim_subs(char **str, int j, char *tmp, char *tmp2);
void		heredoc_monitor(char **line, char *prompt, char *delim, int *fd);

/*---------------------------------HISTORY-----------------------------------*/

void		ft_init_history_file(t_minishell *boogeyman);
void		ft_history_filler(t_minishell *boogeyman);
void		ft_add_history(char *str, t_minishell *boogeyman);

// init

void		init(t_minishell *boogeyman, char **envp, int argc, char **argv);

/*---------------------------------TOKENIZER---------------------------------*/

t_list		*tokenizer(char *str);
char		ft_isreserved(char c);
void		state_quote_delimiter(char *str, int *i, char delim);
int			ft_remove_quotes(t_list *tokens);
int			ft_exec_and_wait(t_ast_tree *tree_node, t_minishell *boogeyman);
void		ft_str_unquote(char *str);
int			retokenize(t_list *curr, int type, int start, int *lngths);

/*---------------------------------BUILTINS----------------------------------*/

int			ft_exit_builtin(t_tree_node *node, t_minishell *boogeyman, char print);
int			ft_cd_builtin(t_tree_node *node, t_minishell *boogeyman);
int			ft_pwd_builtin(t_tree_node *node, char **envp);
int			ft_echo_builtin(t_tree_node *node);
int			ft_export_builtin(t_tree_node *node, t_minishell *boogeyman);
int			ft_unset_builtin(t_tree_node *node, t_minishell *boogeyman);
int			ft_isbuiltin(char *str);

/*---------------------------------EXECUTION---------------------------------*/

int			execute(t_ast_tree *tree_node, t_minishell *boogeyman);
int			expand_execute(t_ast_tree *tree_node, t_minishell *boogeyman);
int			ft_parse_and_exec_monitor(t_ast_tree *tree_node, t_minishell *boogeyman);
char		*ft_remove_brackets(char *str);
int			logic_expansion(t_ast_tree *tree_node);
void		ft_remove_outer_brackets(char *str);
int			get_log_expandible(char *str);
void		is_quote(char *str, int *i, int *last);
int			if_mask(char *str, int last);
char		*ft_get_left_token(char *str);
char		*ft_get_right_token(char *str);
void		ft_brackets(char *str, int *i);
char		ft_has_brackets(char *str);
void		ft_expansion_error(t_ast_tree *tree_node);
void		ft_fork(t_tree_node *node);
t_tree_node	*ft_pipes_interpreter(t_ast_tree *tree_node, t_minishell *boogeyman,
				int *last_pid);
int			ft_file_redirs(t_list *files, int input_fd, int output_fd,
				char **envp);
int			ft_exec_first_cmd(t_tree_node *node, t_minishell *boogeyman,
				int *outfd);
int			exec_first_management(t_tree_node *node, t_minishell *boogeyman,
				char **path);
int			ft_exec_single_cmd(t_tree_node *node, t_minishell *boogeyman);
int			ft_no_path(t_tree_node *node, int close, int fd);
char		*extract_exec_path(t_minishell *boogeyman, t_tree_node *node);
void		ft_execbuiltin(t_tree_node *node, t_minishell *boogeyman, char parent);

/*---------------------------------EXPANDER----------------------------------*/

char		*dictionary(char *str, int needle_tip);
char		*ft_expand_str(char *line, char **envp, char expand_all);
int			ft_expand_str_list(t_list *list, t_minishell *boogeyman);
void		expand_list_tokens(t_list *curr, t_minishell *boogeyman);
void		wildcard_expander(t_list *curr, int *i);
void		env_expander(t_list *curr, int *i, int check_w_cards,
				t_minishell *boogeyman);
void		double_quote_expander(t_list *curr, int *i, t_minishell *boogeyman);
void		single_quote_expander(t_list *curr, int *i);

int			ft_open(t_redirection_token *f_tok);
void		ft_close(int fd);
void		ft_dup2(int oldfd, int newfd);

/*--------------------------------SINTAX CHECKER-----------------------------*/

int			ft_check_syntax_heredoc(t_minishell *boogeyman);
void		ft_print_syntax_error(char *str);
int			ft_check_quotes(char *str);
int			ft_check_brackets(char *str);
int			ft_create_heredocs(char **str);
int			ft_check_fredirs(char *str);


/*------------------------------SIGNALS----------------------------*/

int			ft_set_signal_print(int val);
int			ft_set_echo(int val);
void		ft_signals(int signum);

/*------------------------------ERRORS-----------------------------*/

void		ft_printexit(int exit_code, t_minishell *boogeyman, char print);
void		ft_free_array(char **array);
void		free_cmd_tok(void *tok);
char		*cwd_str_status(void);
void		ft_memory_err_exit(t_minishell *boogeyman);
void		tmp_management(char **tmp, int *shllvl);
int			ft_file_name_checker(char *str, int *i);

/*------------------------------WILDCARDS----------------------------*/

char		*ft_wildcard(char *wc);
char		*ft_expand_str_wildcards(char *str);
void		wildcard_process(int *conts, char *f_name, char *wc);
int			strlen_and_free(char **tmp, char **tmp2, char **file);
void		get_files_init(DIR **dir_ptr, struct dirent **directory);
int			wc_iterator(char *wc, char *f_name, int *j, int i);
char		*get_host_name(void);
char		*process_directory(char *original_dir, char *home);
char		*build_prompt(char *user, char *host, char *dir);
char		*ft_prompt(char **env);
void		update_prompt(t_minishell *boogeyman);

#endif
