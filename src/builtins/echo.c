/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:52:47 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/10 20:58:02 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Manages the arguments for the echo command.
 *
 * This function processes the arguments passed to the echo command,
 * specifically looking for the "-n" flag which indicates that no newline
 * should be printed at the end of the output. It updates the indices and
 * flag accordingly.
 *
 * @param node The tree node containing the command arguments.
 * @param i Pointer to the index of the current argument being processed.
 * @param j Pointer to the index within the current argument string.
 * @param flag Pointer to the flag indicating whether the "-n" option is present.
 */
static void	node_args_management(t_tree_node *node, int *i, int *j, char *flag)
{
	if (node->args[1])
	{
		while (node->args[*i] && !ft_strncmp("-n", node->args[*i], 2))
		{
			*j = 0;
			while (node->args[*i][++(*j)])
				if (node->args[*i][*j] != 'n')
					break ;
			if (node->args[*i][*j])
				break ;
			*flag = 1;
			++(*i);
		}
	}
}

/**
 * @brief Executes the echo built-in command.
 *
 * This function implements the echo command, which prints its arguments
 * to the standard output. It handles the "-n" flag to suppress the trailing
 * newline character. If the command is not executed in a child process,
 * it prints each argument followed by a space, and optionally a newline.
 *
 * @param node The tree node containing the command arguments.
 * @return Always returns 0.
 */
int	ft_echo_builtin(t_tree_node *node)
{
	char	flag;
	int		i;
	int		j;

	flag = 0;
	i = 1;
	node_args_management(node, &i, &j, &flag);
	if (!node->pid)
	{
		while (node->args[i])
		{
			ft_putstr_fd(node->args[i], STDOUT_FILENO);
			if (node->args[i + 1])
				ft_putstr_fd("", STDOUT_FILENO);
			++i;
		}
		if (!flag)
			ft_putendl_fd("", STDOUT_FILENO);
	}
	return (0);
}
