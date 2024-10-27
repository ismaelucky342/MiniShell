/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:19:29 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/10/27 17:42:29 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*COsas q voy necesitando
ft_isbuiltin()

int	ft_isbuiltin(char *str)
{
    if (!ft_strncmp(str, "cd", 3))
        return (KO);
    ...
    return (OK);
}

APROX

int			ft_exec_single_cmd(t_tree_node *node, t_minishell *boogeyman);
int         ft_exec_first_cmd(t_tree_node *node, t_minishell *boogeyman);
int         ft_exec_mid_cmd(t_tree_node *node, t_minishell *boogeyman);
*/
t_tree_node	*ft_interpreter(t_ast_tree *node, t_minishell *boogeyman, int *lastpid)
{
	t_tree_node	*list = node->cmd_list;
	int			fd_input = 0;
	int			fd_output = 0;

	if (!list->next)
	{
		ft_exec_single_cmd(list, boogeyman);
		*lastpid = list->pid;
		return (list);
	}
	if (ft_exec_first_cmd(list, boogeyman, &fd_output) == KO)
		return (NULL);
	list = list->next;
	fd_input = fd_output;
	while (list->next)
	{
		if (ft_exec_mid_cmd(list, boogeyman, fd_input, &fd_output) == KO)
			return (NULL);
		fd_input = fd_output;
		list = list->next;
	}
	if (ft_exec_last_cmd(list, boogeyman, fd_input) == KO)
		return (NULL);
	*lastpid = list->pid;
	return (list);
}
