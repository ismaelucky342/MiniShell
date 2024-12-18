/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:52:47 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/18 11:16:50 by dgomez-l         ###   ########.fr       */
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

	* @param flag Pointer to the
	flag indicating whether the "-n" option is present.
 */
static void	n_args_mg(t_tree_node *node, int *i, int *j, char *flag)
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
static void	print_echo_arguments(t_tree_node *node, int i, char flag)
{
	while (node->args[i])
	{
		if (node->args[i][0] == '"' && node->args[i][ft_strlen(node->args[i])
			- 1] == '"')
		{
			node->args[i][ft_strlen(node->args[i]) - 1] = '\0';
			ft_putstr_fd(node->args[i] + 1, STDOUT_FILENO);
		}
		else
			ft_putstr_fd(node->args[i], STDOUT_FILENO);
		if (node->args[i + 1] && node->args[i + 1][0] != ':'
			&& node->args[i][ft_strlen(node->args[i]) - 1] != ':')
			ft_putstr_fd(" ", STDOUT_FILENO);
		++i;
	}
	if (!flag)
		ft_putendl_fd("", STDOUT_FILENO);
}

int	ft_echo_builtin(t_tree_node *node)
{
	char	flag;
	int		j;
	int		i;

	flag = 0;
	j = 0;
	i = 1;
	n_args_mg(node, &i, &j, &flag);
	if (!node->pid)
		print_echo_arguments(node, i, flag);
	return (0);
}
