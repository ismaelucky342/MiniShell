/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:56:09 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/08/31 16:56:36 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	t_delete(t_token **token)
{
	t_token		*tmp;

	if (!*token)
		return ;
	tmp = *token;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (*token == tmp)
		*token = tmp->next;

	free(tmp->value);
	free(tmp);
}

void	t_delete_all(t_token **tokens)
{
	t_token		*tmp;

	if (!*tokens)
		return ;

	while ((*tokens)->prev)
		*tokens = (*tokens)->prev;

	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		t_delete(&tmp);
	}
}

t_token	*add_token(t_token *token_last, t_token_type token_type)
{
	t_token		*new_token;

	if (token_last && token_last->type == T_WORD && token_type == T_WORD)
		return (token_last);
	if (token_last && token_last->type == T_SEPARATOR)
	{
		token_last->type = token_type;
		return (token_last);
	}
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);

	new_token->next = NULL;
	new_token->prev = token_last;
	new_token->type = token_type;
	new_token->value = NULL;
	new_token->quotes = 0;

	if (token_last)
		token_last->next = new_token;

	return (new_token);
}

t_token	*token_split(t_token *tokens, int direction)
{
	t_token	*tmp;

	if (!tokens)
		return (NULL);

	if (direction == 1)
	{
		tmp = tokens->next;
		tokens->next = NULL;

		if (tmp)
			tmp->prev = NULL;
		return (tmp);
	}
	tmp = tokens->prev;
	tokens->prev = NULL;
	if (tmp)
		tmp->next = NULL;
	return (tmp);
}

t_token	*parentesistesis(t_token *tokens, int direction)
{
	int		level = 1;

	while (tokens && level > 0)
	{
		if (direction == 1)
			tokens = tokens->next;
		else
			tokens = tokens->prev;

		if (tokens)
		{
			if (tokens->type == T_Lparentesis)
				level += direction;
			else if (tokens->type == T_Rparentesis)
				level -= direction;
		}
	}

	return (tokens);
}
