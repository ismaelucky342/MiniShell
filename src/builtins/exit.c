/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:54:10 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:34:07 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * ft_check_exit_arg - Checks if the given argument is a valid numeric argument
 *                     for the exit command.
 * @arg: The argument to check.
 *
 * This function verifies if the provided argument is a valid numeric string
 * that can be used with the exit command. It allows for an optional sign
 * ('+' or '-') and ensures that the argument consists of digits and optional
 * whitespace. The function returns 1 if the argument is valid, otherwise 0.
 *
 * Return: 1 if the argument is a valid numeric string, 0 otherwise.
 */
static int	ft_check_exit_arg(char *arg)
{
	int	i;
	int	sign_ctr;
	int	digits;

	i = -1;
	sign_ctr = 0;
	digits = 0;
	while (arg[++i] && sign_ctr <= 1)
	{
		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]) && (arg[i] != '+'
				&& arg[i] != '-'))
			return (0);
		if (arg[i] == '+' || arg[i] == '-')
			++sign_ctr;
		if (ft_isdigit(arg[i]))
			++digits;
	}
	if (sign_ctr <= 1 && digits >= 1 && digits <= 20)
		return (1);
	return (0);
}

/**
 * ft_exit_builtin - Handles the exit command for the minishell.
 * @node: The current command node containing arguments.
 * @boogeyman: The minishell instance.
 * @print: A flag indicating whether to print the exit status.
 *
 * This function processes the exit command in the minishell. It checks the
 * provided arguments to ensure they are valid. If the first argument is
 * present and valid, it converts it to an integer and exits with that status.
 * If there are too many arguments or the argument is not numeric, it prints
 * an error message and exits with a status of 2. If no arguments are provided,
 * it exits with a status of 0.
 *
 * Return: 0 on successful exit, 1 if there are too many arguments.
 */
int	ft_exit_builtin(t_tree_node *node, t_mini *boogeyman, char print)
{
	if (node->args[0] && node->args[1])
	{
		if (!ft_check_exit_arg(node->args[1]))
		{
			ft_putendl_fd("MiniShell: exit: numeric arg required",
				STDERR_FILENO);
			ft_printexit(2, boogeyman, print);
		}
		if (node->args[2] != NULL)
		{
			ft_putendl_fd("MiniShell: exit: too many arguments", STDERR_FILENO);
			return (1);
		}
		ft_printexit(ft_atoi(node->args[1]), boogeyman, print);
	}
	ft_printexit(0, boogeyman, print);
	return (0);
}
