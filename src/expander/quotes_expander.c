/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:26:59 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:39:10 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * double_quote_expander - Expands double-quoted strings in the token.
 * @param curr: The current node in the list containing the token.
 * @param i: Pointer to the current index in the token string.
 * @param boogeyman: Pointer to the minishell structure containing
		env variables.
 *
 * This function removes the double quotes from the token string and expands
 * any env variables within the double quotes.
 */
void	double_quote_expander(t_list *curr, int *i, t_mini *boogeyman)
{
	int			j;
	t_token		*tok;

	j = *i;
	tok = curr->content;
	while (tok->str[j])
	{
		tok->str[j] = tok->str[j + 1];
		++j;
	}
	while (tok->str[*i] != '"' && tok->str[*i])
	{
		if (tok->str[*i] == '$')
			env_expander(curr, i, 0, boogeyman);
		else
			++(*i);
	}
	j = *i;
	while (tok->str[j] && tok->str[j + 1])
	{
		tok->str[j] = tok->str[j + 1];
		++j;
	}
	tok->str[j] = '\0';
}

/**
 * single_quote_expander - Expands single-quoted strings in the token.
 * @curr: The current node in the list containing the token.
 * @i: Pointer to the current index in the token string.
 *
 * This function removes the single quotes from the token string. env
 * variables are not expanded within single quotes.
 */
void	single_quote_expander(t_list *curr, int *i)
{
	int			j;
	t_token		*tok;

	j = *i;
	tok = curr->content;
	while (tok->str[j])
	{
		tok->str[j] = tok->str[j + 1];
		++j;
	}
	while (tok->str[*i] != '\'' && tok->str[*i])
		++(*i);
	j = *i;
	while (tok->str[j] && tok->str[j + 1])
	{
		tok->str[j] = tok->str[j + 1];
		++j;
	}
	tok->str[j] = '\0';
}
