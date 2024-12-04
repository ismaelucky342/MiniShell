/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:23:19 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/12/04 16:13:29 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_check_exit_arg(char *arg)
{
	int		i;
	int		sign_ctr;
	int		digits;

	i = -1;
	sign_ctr = 0;
	digits = 0;
	while (arg[++i] && sign_ctr <= 1)
	{
		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i])
			&& (arg[i] != '+' && arg[i] != '-'))
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

int	ft_msh_exit(t_tree_node *node, t_minishell *sack, char print)
{
	if (node->args[0] && node->args[1])
	{
		if (!ft_check_exit_arg(node->args[1]))
		{
			ft_putendl_fd("Minishell: exit status: numeric arg required",
				STDERR_FILENO);
			ft_exit_msg(2, sack, print);
		}
		if (node->args[2] != NULL)
		{
			ft_putendl_fd("Minishell: exit status: too many arguments", STDERR_FILENO);
			return (1);
		}
		ft_exit_msg(ft_atoi(node->args[1]), sack, print);
	}
	ft_exit_msg(0, sack, print);
	return (0);
}