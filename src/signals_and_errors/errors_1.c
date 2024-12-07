/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:07:54 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/07 22:30:49 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_memory_err_exit(t_mini *boogeyman)
{
	ft_putendl_fd("MiniShell: memory error", STDERR_FILENO);
	ft_printexit(2, boogeyman, 0);
}

void	tmp_management(char **tmp, int *shllvl)
{
	ft_putstr_fd("MiniShell: warning: shell level (", STDERR_FILENO);
	*tmp = ft_itoa(*shllvl);
	ft_putstr_fd(*tmp, STDERR_FILENO);
	freedom((void **)&*tmp);
	*tmp = NULL;
	ft_putendl_fd(") too high, resetting to 1", STDERR_FILENO);
	*shllvl = 1;
}

/**
 * Prints a syntax error message to the standard error output.
 *
 * @param str The error message to be printed.
 */
void	ft_print_syntax_error(char *str)
{
	ft_putstr_fd("MiniShell: syntax error: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}
