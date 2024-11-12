/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:57:18 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/12 11:27:32 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Removes line numbers and adjusts indices in the token string.
 *
 * This function processes the token to remove any line numbers and adjusts
 * the indices in the `cont` array to indicate the positions in `tok->str`.
 *
 * @param tok Token containing the string to process.
 * @param cont Array of indices used to track positions within `tok->str`.
 */
static void remove_line_numbers(t_token *tok, int *cont)
{
	while (cont[2] > 0 && !ft_isspace(tok->str[cont[2]]))
		--cont[2];
	while (ft_isspace(tok->str[cont[2]]))
		++cont[2];
	while (tok->str[cont[1]] && !ft_isspace(tok->str[cont[1]]))
		++cont[1];
}

/**
 * @brief Merges parts of the token string with expanded wildcard matches.
 *
 * This function builds a new token string by concatenating substrings
 * before and after the expanded wildcard match.
 *
 * @param tok Token containing the original string.
 * @param cont Array of indices tracking positions within `tok->str`.
 * @param files Pointer to the string with wildcard matches.
 * @param regex Pointer to the string with regex for matching.
 */
static void merge_strings(t_token *tok, int *cont, char **files, char **regex)
{
	char *tmp;

	tmp = ft_substr(tok->str, 0, cont[2]);
	*regex = ft_strjoin(tmp, *files);
	free(*files);
	free(tmp);
	*files = ft_strjoin(*regex, &(tok->str[cont[1]]));
	free(*regex);
	free(tok->str);
}

/**
 * @brief Expands wildcard patterns in the current token.
 *
 * The function takes the current token and replaces any wildcard patterns
 * with matching files. It performs the expansion using the indices in `cont`
 * to manipulate the string, replacing `tok->str` with the expanded string
 * and updating the token type.
 *
 * @param curr Current list node containing `tok`.
 * @param i Index of the current position within `tok->str`.
 */
void wildcard_expand(t_list *curr, int *i)
{
	int	cont[3];
	t_token *tok;
	char *regex;
	char *files;

	cont[1] = *i + 1;
	cont[2] = *i;
	tok = curr->data;
	remove_line_numbers(tok, cont);
	cont[1] = *i;
	while (tok->str[cont[1]] && !ft_isspace(tok->str[cont[1]]))
		++cont[1];
	regex = ft_substr(tok->str, cont[2], cont[1] - cont[2]);
	files = ft_wildcards(regex);
	free(regex);
	if (!files)
		return (tok->type = W_EXP_ARG, (void) 0);
	merge_strings(tok, cont, &files, &regex);
	tok->str = files;
	cont[0] = ft_strlen(files) + *i;
	retokenize(curr, W_EXP_ARG, cont[2], cont);
	if (tok != curr->data)
		free_cmd_token(tok);
}
