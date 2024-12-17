/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:16:39 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/15 17:51:45 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Advances the pointer within a string until a specified delimiter or the end
 * of the string is reached.
 *
 * @param str The input string.
 * @param i Pointer to the current index in the string, which will be updated.
 * @param delim The delimiter character to search for.
 */
void	state_quote_delimiter(char *str, int *i, char delim)
{
	++(*i);
	while (str[*i] != delim && str[*i])
		++(*i);
}

/**
 * Removes surrounding quotes from a string by shifting its characters.
 * Both single (`'`) and double (`"`) quotes are handled.
 *

	* @param str The input string to unquote. This string will 
	be modified in place.
 */
void	ft_str_unquote(char *str)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			j = i + 1;
			while (str[j] && str[j] != str[i])
				++j;
			tmp = --j;
			while (str[++j])
				str[j] = str[j + 1];
			--i;
			while (str[++i])
				str[i] = str[i + 1];
			i = tmp;
		}
		else
			++i;
	}
}

/**
 * Removes quotes from all strings in a linked list of tokens.
 *
 * @param tokens A linked list where each node contains a `t_token` structure.
 *               The `str` field of each `t_token` will be unquoted.
 * @return Always returns 0 to indicate success.
 */
int	ft_remove_quotes(t_list *tokens)
{
	t_token	*content;

	while (tokens)
	{
		content = tokens->content;
		ft_str_unquote(content->str);
		tokens = tokens->next;
	}
	return (0);
}
