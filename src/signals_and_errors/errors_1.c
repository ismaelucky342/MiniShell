/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:07:54 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 12:56:29 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_memory_err_exit(t_minishell *boogeyman)
{
	ft_putendl_fd("MiniShell: memory error", STDERR_FILENO);
	ft_printexit(2, boogeyman, 0);
}

void	tmp_management(char **tmp, int *shllvl)
{
	ft_putstr_fd("MiniShell: warning: shell level (", STDERR_FILENO);
	*tmp = ft_itoa(*shllvl);
	ft_putstr_fd(*tmp, STDERR_FILENO);
	free(*tmp);
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
