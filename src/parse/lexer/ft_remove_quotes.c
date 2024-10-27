/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:30:31 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 17:29:22 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	skip_to_delimiter(char *str, int *i, char delim)
{
	++(*i);
	while (str[*i] != delim && str[*i])
		++(*i);
}

void	ft_str_unquote(char *str)
{
	int		i;
	char	delim;
	int		start;
	int		end;
	int		j;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			delim = str[i];
			start = i;
			skip_to_delimiter(str, &i, delim);
			end = i;
			j = end + 1;
			while (str[j])
			{
				str[start++] = str[j++];
			}
			str[start] = '\0';
			i = start - 1;
		}
		++i;
	}
}

int	ft_remove_quotes(t_list *tokens)
{
	t_token	*content;

	while (tokens)
	{
		content = tokens->data;
		ft_str_unquote(content->str);
		tokens = tokens->next;
	}
	return (OK);
}
