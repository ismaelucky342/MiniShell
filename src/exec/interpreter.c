/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:19:29 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/10/01 18:32:20 by ismherna         ###   ########.fr       */
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

int			ft_exec_single_cmd(t_tree_node *node, t_minishell *sack);
int         ft_exec_first_cmd(t_tree_node *node, t_minishell *sack);
int         ft_exec_mid_cmd(t_tree_node *node, t_minishell *sack);
*/
t_tree_node	*ft_interpreter(t_ast_tree *node, t_minishell *sack, int *lastpid)
{
	t_tree_node		*list;
	int				fd_input;
	int				fd_output;

	fd_input = 0;
	fd_output = 0;
	list = node->cmd_list;
	if (!list->next)
		return (ft_exec_single_cmd(list, sack), *lastpid = list->pid, list);
	// Ejecuta el comando,Almacena el PID del último comando.
	// Devuelve el nodo del comando.
	// Si hay múltiples comandos en la lista, ejecuta el primer comando.
	ft_exec_first_cmd(list, sack, &fd_input);
	list = list->next; // Avanza al siguiente comando.
	// Ejecuta los comandos intermedios de la lista.
	while (list->next)
	{
		ft_exec_mid_cmd(list, sack, fd_input, &fd_output);
			// Ejecuta el comando intermedio.
		fd_input = fd_output;
			// Actualiza el descriptor de entrada para el siguiente comando.
		list = list->next;
			// Avanza al siguiente comando.
	}
	// Ejecuta el último comando de la lista y almacena el PID del último.
	return (ft_exec_last_cmd(list, sack, fd_input), *lastpid = list->pid, list);
}
