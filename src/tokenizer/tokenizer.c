/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:44:47 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/07 22:30:49 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Extracts a token from the input string based on the given range and type.
 *
 * @param str The input string.
 * @param start The start index of the token in the input string.
 * @param end The end index of the token in the input string.
 * @return A pointer to a newly created token structure, or NULL on failure.
 */
static void	*get_token(char *str, int start, int end)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_substr(str, start, end - start);
	token->type = ARG;
	if (!ft_strncmp(token->str, "<", 2) || !ft_strncmp(token->str, "<<", 3)
		|| !ft_strncmp(token->str, ">", 2) || !ft_strncmp(token->str, ">>", 3))
		token->type = FILE_REDIR;
	else if (!ft_strncmp(token->str, "|", 2))
		token->type = PIPE;
	else if (!ft_strncmp(token->str, "&&", 3) || !ft_strncmp(token->str, "||",
			3) || !ft_strncmp(token->str, ";", 2))
		token->type = LOGIC;
	return ((void *)token);
}

/**
 * Extracts the next token from the input string, handling special cases
 * like quotes and reserved characters.
 *
 * @param str The input string.
 * @param start The starting index for token extraction.
 * @param i A pointer to the current index being processed in the input string.
 * @return A pointer to a newly created token, or NULL on failure.
 */
static void	*get_next_token(char *str, int start, int *i)
{
	while (str[*i] && !ft_isspace(str[*i]))
	{
		if (str[*i] == '\'')
			state_quote_delimiter(str, i, '\'');
		else if (str[*i] == '\"')
			state_quote_delimiter(str, i, '\"');
		if (ft_isreserved(str[*i]))
			break ;
		if (str[*i] && !ft_isspace(str[*i]))
			++(*i);
	}
	if (ft_isreserved(str[*i]) && start == *i)
	{
		++(*i);
		if (str[*i] == str[(*i) - 1])
			(*i) += 1;
	}
	return (get_token(str, start, *i));
}

/**
 * Tokenizes the input string into a linked list of tokens.
 *
 * @param str The input string to tokenize.
 * @param list The linked list to store tokens.
 * @return 0 on success, 1 on failure.
 */
static int	tokener(char *str, t_list *list)
{
	t_list	*current;
	t_list	*last;
	int		i;
	int		start;

	i = 0;
	current = list;
	last = NULL;
	while (str[i])
	{
		skip_spaces(str, &i, &start, 1);
		last = current;
		current->content = get_next_token(str, start, &i);
		current->next = ft_calloc(1, sizeof(t_list));
		if (!current->content || !current->next)
			return (1);
		current = current->next;
	}
	if (last)
	{
		freedom((void **)&last->next);
		last->next = NULL;
	}
	return (0);
}

/**
 * Tokenizes a string into a list of tokens, allocating memory for the list
 * and processing each token.
 *
 * @param str The input string to tokenize.
 * @return A pointer to the linked list of tokens, or NULL on failure.
 */
t_list	*tokenizer(char *str)
{
	t_list	*list;

	list = ft_calloc(1, sizeof(t_list));
	if (!list)
		return (NULL);
	if (tokener(str, list))
		return (ft_lstclear(&list, free_cmd_tok), NULL);
	return (list);
}
