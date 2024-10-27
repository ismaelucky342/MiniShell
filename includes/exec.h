/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:48:30 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/10/27 17:11:32 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

/*
ARBOL DE PRIORIDADES:
1. ()
1. && / ||
2. REDIRS
3. PIPES
*/

int			isbuiltin(char *str);
int			ms_exit(t_tree_node *node, t_minishell *boogeyman, char print);
int			ms_change_dir(t_tree_node *node, t_minishell *boogeyman);
int			ms_print_working_dir(t_tree_node *node, char **envp);
int			ms_echo(t_tree_node *node);
int			ms_export(t_tree_node *node, t_minishell *boogeyman);
int			ms_unset(t_tree_node *node, t_minishell *boogeyman);

//execute (2,3,4)

char		*remove_brackets(char *str);
int			logic_expansion(t_ast_tree *tree_node);
void		remove_outer_brackets(char *str);
int			get_log_expandible(char *str);
void		is_quote(char *str, int *i, int *last);
int			if_mask(char *str, int last);
void		brackets(char *str, int *i);
char		has_brackets(char *str);
void		expansion_error(t_ast_tree *tree_node);

//execute_utils (1)

t_tree_node	*execute_lst(t_ast_tree *tree_node,
				t_minishell *boogeyman, int *last_pid);
int			file_redirs(t_list *files, int input_fd, int output_fd,
				char **envp);
int			exec_single_cmd(t_tree_node *node, t_minishell *boogeyman);
int			exec_first_cmd(t_tree_node *node, t_minishell *boogeyman,
				int *outfd);
int			exec_first_management(t_tree_node *node, t_minishell *boogeyman,
				char **path);
int			no_path(t_tree_node *node, int close, int fd);

#endif