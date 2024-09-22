/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:37:00 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/20 17:29:45 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	*add_token(char *str, int start, int end, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_substr(str, start, end - start);
	token->type = type;
	return ((void *) token);
}

static void	*add_token_next(char *str, int type, int *conts, int len)
{
	while (str[conts[0]] && !ft_isspace(str[conts[0]]))
		++(conts[0]);
	while (str[conts[0]] && conts[0] >= len)
		++(conts[0]);
	return (add_token(str, conts[1], conts[0], type));
}

static void	node(t_list **last_next, int *conts,
	int *lngths)
{
	t_list	*last;
	t_list	*next;

	last = last_next[0];
	next = last_next[1];
	if (last && last->next)
	{
		free(last->next);
		last->next = next;
		if (conts[0] > lngths[0])
			((t_token *)last->data)->type = ARG;
	}
}

static	void	free_tmp(char *tmp)
{
	if (tmp)
		free(tmp);
}

int	retokenize(t_list *curr, int type, int start, int *lngths)
{
	int		conts[2];
	char	*tmp;
	t_list	*last_next[2];

	conts[0] = start;
	last_next[0] = NULL;
	last_next[1] = NULL;
	tmp = ft_strdup(((t_token *)curr->data)->str);
	conts[1] = 0;
	last_next[1] = curr->next;
	while (tmp && tmp[conts[0]])
	{
		skip_spaces(tmp, &conts[0], &conts[1], 0);
		last_next[0] = curr;
		curr->data = add_token_next(tmp, type, conts, lngths[0]);
		if (!lngths[1])
			lngths[1] = conts[0];
		curr->next = ft_calloc(1, sizeof(t_list));
		if (!curr->data || !curr->next)
			return (1);
		skip_spaces(tmp, &conts[0], &conts[1], 1);
		curr = curr->next;
	}
	node(last_next, conts, lngths);
	return (free_tmp(tmp), 0);
}
