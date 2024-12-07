/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:27:42 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:26:28 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief remove_line_numbers
 * 
 * Adjusts the indices in the token string to remove line numbers.
 * 
 * @param tok: The token containing the string to be processed.
 * @param cont: An array of ints used to keep track of indexes in the
		token string.
 *
 * This function modifies the indices in the cont array to skip over
		line numbers
 * and whitespace in the token string.
 */
static void	remove_line_numbers(t_token *tok, int *cont)
{
	while (cont[2] > 0 && !ft_isspace(tok->str[cont[2]]))
		--cont[2];
	while (ft_isspace(tok->str[cont[2]]))
		++cont[2];
	while (tok->str[cont[1]] && !ft_isspace(tok->str[cont[1]]))
		++cont[1];
}

/**
 * merge_strings
	- Merges parts of the token string with the files and wc strings.
 * @param tok: The token containing the string to be processed.
 * @param cont: An array of integers used to keep track of indices in
		the token string.
 * @param files: A pointer to the string containing file names.
 * @param wc: A pointer to the string containing the wc pattern.
 *
 * This function creates a new string by merging parts of the token string with
 * the files and wc strings, and updates the token string with the result.
 */
static void	merge_strings(t_token *tok, int *cont, char **files, char **wc)
{
	char	*tmp;

	tmp = ft_substr(tok->str, 0, cont[2]);
	*wc = ft_strjoin(tmp, *files);
	free(*files);
	free(tmp);
	*files = ft_strjoin(*wc, &(tok->str[cont[1]]));
	free(*wc);
	free(tok->str);
}

/**
 * wildcard_expander - Expands wildcard patterns in the token string.
 * @curr: The current list node containing the token to be processed.
 * @i: A pointer to the current index in the token string.
 *
 * This function processes the token string to expand wildcard patterns,
	updating
 * the token string with the expanded result and retokenizing the list node.
 */
void	wildcard_expander(t_list *curr, int *i)
{
	int			cont[3];
	t_token		*tok;
	char		*wc;
	char		*files;

	cont[1] = *i + 1;
	cont[2] = *i;
	tok = curr->content;
	remove_line_numbers(tok, cont);
	cont[1] = *i;
	while (tok->str[cont[1]] && !ft_isspace(tok->str[cont[1]]))
		++cont[1];
	wc = ft_substr(tok->str, cont[2], cont[1] - cont[2]);
	files = ft_wildcard(wc);
	free(wc);
	if (!files)
		return (tok->type = W_EXP_ARG, (void)0);
	merge_strings(tok, cont, &files, &wc);
	tok->str = files;
	cont[0] = ft_strlen(files) + *i;
	retokenize(curr, W_EXP_ARG, cont[2], cont);
	if (tok != curr->content)
		free_cmd_tok(tok);
}
