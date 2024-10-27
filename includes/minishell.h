/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:51:34 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 23:02:25 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include "colors.h"
# include "parse.h"
# include "exec.h"
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

# define PB "\001\x1b[32m\002Minishell\001\x1b[0m\002 - \001\x1b[31m\002"
# define HIST_ERROR_MSG "Minishell: HOME is not set, history unavailable."
# define H_DOC_TMP_BASE "/tmp/.dash_tmp_heredoc_"
# define HIST_TMP_BASE "/.dash_history"
# define FILE_REDIR 0
# define PIPE 1
# define LOGIC 2

//expander

char		*ft_expand(char *line, char **envp, char expand_all);
int			ft_list_expand(t_list *list, t_minishell *boogeyman);
void		list_expand(t_list *curr, t_minishell *boogeyman);

void		wildcard_expand(t_list *curr, int *i);
void		ft_expand_env(t_list *curr, int *i, int check_w_cards,
				t_minishell *boogeyman);
void		double_quote_expand(t_list *curr, int *i, t_minishell *boogeyman);
void		single_quote_expand(t_list *curr, int *i);

//redirect_utils

int			ft_open(t_redirection_token *f_tok);
void		ft_close(int fd);
void		ft_dup2(int oldfd, int newfd);

//syntax_checker

int			ft_check_heredoc(t_minishell *boogeyman);
void		ft_syntax_error(char *str);
void		ft_quote_error(void);
void		ft_bracket_error(void);
int			ft_create_heredocs(char **str);
int			ft_check_quotes(char *str);
int			ft_check_brackets(char *str);
int			ft_check_fredirs(char *str);
void		skip_to_delimiter(char *str, int *i, char delim);
//path_finder

char		*extract_exec_path(t_minishell *boogeyman, t_tree_node *node);
void		ft_execbuiltin(t_tree_node *node, t_minishell *boogeyman, char parent);

//term_settings

int			ft_set_signal(int val);
int			ft_set_echo(int val);

//utils

void		ft_exit_msg(int exit, t_minishell *boogeyman, char print);
void		ft_array_free(char **array);
void		free_cmd_token(void *tok);
char		*get_cwd_str(void);
void		ft_memory_error(t_minishell *boogeyman);
void		ft_tmp(char **tmp, int *chell);
int			ft_check_file(char *str, int *i);

#endif
