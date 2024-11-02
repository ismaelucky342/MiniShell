/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:58:02 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/02 22:40:18 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	double_quote_expand(t_list *curr, int *i, t_minishell *boogeyman)
{
	int		j;
	t_token	*tok;

	j = *i;
	tok = curr->data;
	while (tok->str[j])
	{
		tok->str[j] = tok->str[j + 1];
		++j;
	}
	while (tok->str[*i] != '"' && tok->str[*i])
	{
		if (tok->str[*i] == '$')
			ft_expand_env(curr, i, 0, boogeyman);
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

void	single_quote_expand(t_list *curr, int *i)
{
	int		j;
	t_token	*tok;

	j = *i;
	tok = curr->data;
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

int	ft_list_expand(t_list *list, t_minishell *boogeyman)
{
	while (list)
	{
		if (((t_token *)list->data)->type == ARG)
			list_expand(list, boogeyman);
		else if (((t_token *)list->data)->type == E_EXP_ARG)
			list_expand(list, boogeyman);
		else
			list = list->next;
	}
	return (OK);
}

void	list_expand(t_list *curr, t_minishell *boogeyman)
{
	t_token	*tok;
	int		i;
	int		pre_type;

	tok = curr->data;
	i = 0;
	pre_type = tok->type;
	while (i < (int)ft_strlen(tok->str))
	{
		if (tok->str[i] == '\'' && pre_type == ARG)
			single_quote_expand(curr, &i);
		else if (tok->str[i] == '"' && pre_type == ARG)
			double_quote_expand(curr, &i, boogeyman);
		else if (tok->str[i] == '*' && pre_type == E_EXP_ARG)
			return (wildcard_expand(curr, &i), (void)0);
		else if (tok->str[i] == '$' && pre_type == ARG)
			ft_expand_env(curr, &i, 1, boogeyman);
		else
			++i;
		tok = curr->data;
	}
	if (pre_type == E_EXP_ARG)
		tok->type = W_EXP_ARG;
	if (pre_type == ARG)
		tok->type = E_EXP_ARG;
}
