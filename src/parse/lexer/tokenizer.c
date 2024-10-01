/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:40:15 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 12:13:16 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_token	*create_token(char *str, int start, int end)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_substr(str, start, end - start);
	if (!token->str)
	{
		free(token);
		return (NULL);
	}
	token->type = ARG;
	if (!ft_strncmp(token->str, "<", 2) || !ft_strncmp(token->str, "<<", 3)
		|| !ft_strncmp(token->str, ">", 2) || !ft_strncmp(token->str, ">>", 3))
		token->type = FILE_REDIR;
	else if (!ft_strncmp(token->str, "|", 2))
		token->type = PIPE;
	else if (!ft_strncmp(token->str, "&&", 3) || !ft_strncmp(token->str, "||",
			3) || !ft_strncmp(token->str, ";", 2))
		token->type = LOGIC;
	return (token);
}

static void	*add_token_next(char *str, int start, int *i)
{
	while (str[*i] && !ft_isspace(str[*i]))
	{
		if (str[*i] == '\'' || str[*i] == '\"')
			skip_to_delimiter(str, i, str[*i]);
		if (ft_is_reserved_char(str[*i]))
			break ;
		++(*i);
	}
	if (ft_is_reserved_char(str[*i]) && start == *i)
	{
		++(*i);
		if (str[*i] == str[*i - 1])
			++(*i);
	}
	return (create_token(str, start, *i));
}

static int	tokener(char *str, t_list *list)
{
	t_list	*current;
	int		i;
	int		start;

	current = list;
	i = 0;
	while (str[i])
	{
		skip_spaces(str, &i, &start, 1);
		current->data = add_token_next(str, start, &i);
		if (!current->data)
			return (KO);
		current->next = ft_calloc(1, sizeof(t_list));
		if (!current->next)
			return (KO);
		current = current->next;
	}
	if (current != list)
	{
		free(current->next);
		current->next = NULL;
	}
	return (OK);
}

t_list	*tokenizer(char *str)
{
	t_list	*list;

	list = ft_calloc(1, sizeof(t_list));
	if (!list)
		return (NULL);
	if (tokener(str, list))
	{
		ft_lstclear(&list, free_cmd_token);
		return (NULL);
	}
	return (list);
}
