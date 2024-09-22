/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:57:18 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:46:08 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_line_numbers(t_token *tok,
		int *cont)
{
	while (cont[2] > 0 && !ft_isspace(tok->str[cont[2]]))
		--cont[2];
	while (ft_isspace(tok->str[cont[2]]))
		++cont[2];
	while (tok->str[cont[1]] && !ft_isspace(tok->str[cont[1]]))
		++cont[1];
}

static void	merge_strings(t_token *tok, int *cont, char **files, char **regex)
{
	char	*tmp;

	tmp = ft_substr(tok->str, 0, cont[2]);
	*regex = ft_strjoin(tmp, *files);
	free(*files);
	free(tmp);
	*files = ft_strjoin(*regex, &(tok->str[cont[1]]));
	free(*regex);
	free(tok->str);
}

void	wildcard_expand(t_list *curr, int *i)
{
	int			cont[3];
	t_token		*tok;
	char		*regex;
	char		*files;

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
