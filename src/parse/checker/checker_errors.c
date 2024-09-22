/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:02:43 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 11:56:14 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_syntax_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error: ", STDERR_FILENO);
	ft_putendl_fd((char *)msg, STDERR_FILENO);
}

void	ft_quote_error(void)
{
	ft_putstr_fd("minishell: unbalanced quotes\n", STDERR_FILENO);
}

void	ft_bracket_error(void)
{
	ft_putstr_fd("minishell: unbalanced parentheses\n", STDERR_FILENO);
}
