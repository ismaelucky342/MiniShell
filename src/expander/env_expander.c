/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:59:26 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 12:32:56 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Joins environment variable value to the token string.
 *
 * This function retrieves the value of an environment variable from the
 * environment list and joins it to the token string. It handles memory
 * allocation and deallocation for the intermediate strings used in the process.
 *
 * @param tok Pointer to the token structure.
 * @param j Index of the current character in the token string.
 * @param tmp Array of temporary strings used for joining.
 * @param boogeyman Pointer to the minishell structure containing environment variables.
 * @return A new string with the environment variable value joined to the token string.
 */
static char	*ft_join_env(t_token *tok, int j, char **tmp, t_minishell *boogeyman)
{
	tmp[2] = ft_strjoin(tmp[1], ft_get_from_env(boogeyman->envp, tmp[0], NULL));
	free(tmp[0]);
	free(tmp[1]);
	tmp[1] = ft_substr(tok->str, j + 1, SIZE_T_MAX);
	tmp[0] = ft_strjoin(tmp[2], tmp[1]);
	free(tmp[1]);
	free(tmp[2]);
	free(tok->str);
	return (tmp[0]);
}

/**
 * @brief Expands environment variables in the token string.
 *
 * This function scans the token string for environment variable references,
 * retrieves their values from the environment list, and replaces the references
 * with the actual values. It also handles retokenization if wildcard characters
 * are present.
 *
 * @param curr Pointer to the current list node containing the token.
 * @param i Pointer to the current index in the token string.
 * @param check_w_cards Flag indicating whether to check for wildcard characters.
 * @param boogeyman Pointer to the minishell structure containing environment variables.
 */
void	env_expander(t_list *curr, int *i, int check_w_cards, t_minishell *boogeyman)
{
	int			j;
	t_token	*tok;
	int			lengths[2];
	char		*tmp[3];

	j = *i;
	lengths[1] = 0;
	tok = curr->content;
	while (tok->str[j + 1] && tok->str[j + 1] != '"' && tok->str[j + 1] != '$'
		&& !ft_isreserved(tok->str[j + 1]) && tok->str[j + 1] != '\''
		&& tok->str[j + 1] != '*' && !ft_isspace(tok->str[j + 1]))
		++j;
	tmp[0] = ft_substr(tok->str, *i + 1, j - *i);
	if (!ft_strncmp(tmp[0], "", 1))
		return (++(*i), free(tmp[0]), (void) 0);
	lengths[0] = ft_strlen(ft_get_from_env(boogeyman->envp, tmp[0], NULL)) + *i;
	tmp[1] = ft_substr(tok->str, 0, *i);
	tok->str = ft_join_env(tok, j, tmp, boogeyman);
	if (check_w_cards)
		retokenize(curr, E_EXP_ARG, *i, lengths);
	*i = lengths[0];
	if (tok != curr->content)
		free_cmd_tok(tok);
	((t_token *) curr->content)->type = E_EXP_ARG;
}
