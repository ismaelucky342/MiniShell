/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:44:47 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 12:49:14 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Creates a new token with the specified string and type.
 *
 * @param str The input string.
 * @param start The starting index of the token in the input string.
 * @param end The ending index of the token in the input string.
 * @param type The type of the token.
 * @return A pointer to the newly created token, or NULL on failure.
 */
static void	*get_token(char *str, int start, int end, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_substr(str, start, end - start);
	token->type = type;
	return ((void *)token);
}

/**
 * Extracts the next token from the input string while skipping whitespace
 * and considering the token type.
 *
 * @param str The input string.
 * @param type The type of the token to be extracted.
 * @param conts Array of indices [current position, start position].
 * @param len The maximum length to process from the input string.
 * @return A pointer to the newly created token, or NULL on failure.
 */
static void	*get_next_token(char *str, int type, int *conts, int len)
{
	while (str[conts[0]] && !ft_isspace(str[conts[0]]))
		++(conts[0]);
	while (str[conts[0]] && conts[0] >= len)
		++(conts[0]);
	return (get_token(str, conts[1], conts[0], type));
}

/**
 * Updates the last node in the token list, freeing any unnecessary nodes
 * and updating token types if necessary.
 *
 * @param last_next Array containing the last node and its next node.
 * @param conts Array of indices [current position, unused].
 * @param lngths Array containing the maximum length and processed length.
 */
static void	update_last_node(t_list **last_next, int *conts, int *lngths)
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
			((t_token *)last->content)->type = ARG;
	}
}

/**
 * Frees a temporary string if it is not NULL.
 *
 * @param tmp The temporary string to free.
 */
static void	free_tmp(char *tmp)
{
	if (tmp)
		free(tmp);
}

/**
 * Retokenizes a node in the token list by splitting its content into smaller
 * tokens and updating the list.
 *
 * @param curr The current node in the token list.
 * @param type The type to assign to new tokens.
 * @param start The starting index for tokenization.
 * @param lngths Array containing [maximum length, processed length].
 * @return 0 on success, 1 on failure.
 */
int	retokenize(t_list *curr, int type, int start, int *lngths)
{
	int		conts[2];
	char	*tmp;
	t_list	*last_next[2];

	conts[0] = start;
	last_next[0] = NULL;
	last_next[1] = NULL;
	tmp = ft_strdup(((t_token *)curr->content)->str);
	conts[1] = 0;
	last_next[1] = curr->next;
	while (tmp && tmp[conts[0]])
	{
		skip_spaces(tmp, &conts[0], &conts[1], 0);
		last_next[0] = curr;
		curr->content = get_next_token(tmp, type, conts, lngths[0]);
		if (!lngths[1])
			lngths[1] = conts[0];
		curr->next = ft_calloc(1, sizeof(t_list));
		if (!curr->content || !curr->next)
			return (1);
		skip_spaces(tmp, &conts[0], &conts[1], 1);
		curr = curr->next;
	}
	update_last_node(last_next, conts, lngths);
	return (free_tmp(tmp), 0);
}
