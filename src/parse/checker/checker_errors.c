/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:02:43 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 17:28:36 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Displays a syntax error message to STDERR.
 *
 * This function prints a generic syntax error message with the
 * specified message content to the standard error.
 *
 * @param msg The specific syntax error message to display.
 */
void ft_syntax_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error: ", STDERR_FILENO);
	ft_putendl_fd((char *)msg, STDERR_FILENO);
}

/**
 * @brief Displays an unbalanced quotes error message.
 *
 * This function prints an error message indicating that quotes
 * are unbalanced in the current command.
 */
void ft_quote_error(void)
{
	ft_putstr_fd("minishell: unbalanced quotes\n", STDERR_FILENO);
}

/**
 * @brief Displays an unbalanced parentheses error message.
 *
 * This function prints an error message indicating that parentheses
 * are unbalanced in the current command.
 */
void ft_bracket_error(void)
{
	ft_putstr_fd("minishell: unbalanced parentheses\n", STDERR_FILENO);
}
