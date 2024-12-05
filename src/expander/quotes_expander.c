/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:26:59 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 12:37:36 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * double_quote_expander - Expands double-quoted strings in the token.
 * @curr: The current node in the list containing the token.
 * @i: Pointer to the current index in the token string.
 * @boogeyman: Pointer to the minishell structure containing environment variables.
 *
 * This function removes the double quotes from the token string and expands
 * any environment variables within the double quotes.
 */

void	double_quote_expander(t_list *curr, int *i, t_minishell *boogeyman)
{
	int			j;
	t_token	*tok;

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
 * This function removes the single quotes from the token string. Environment
 * variables are not expanded within single quotes.
 */
void	single_quote_expander(t_list *curr, int *i)
{
	int			j;
	t_token	*tok;

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