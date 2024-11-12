/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:51:48 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/12 11:27:32 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
* @brief Expands the value of an environment variable.
*
* Given the variable name `var_name`, gets its value from the
* environment stored in `boogeyman->envp`.
*
* @param var_name Name of the environment variable to expand.
* @param boogeyman Pointer to the `t_minishell` structure containing the `envp` environment.
* @return Value of the environment variable as a string.
*/
static char *ft_expand_variable(char *var_name, t_minishell *boogeyman)
{
	return (get_value_from_env(boogeyman->envp, var_name, NULL));
}

/**
* @brief Merges an expanded environment variable with the contents of a token.
*
* Uses `tmp` to handle the parts of the original string and the expanded value of the variable.
* Reconstructs the token string `tok->str` with the expanded value and the remaining fragments of `tok->str`.
*
* @param tok Token containing the original string with the variable.
* @param j End index of the variable name in `tok->str`.
* @param tmp Array of pointers to the substrings and expanded string.
* @param boogeyman Structure `t_minishell` with the environment `envp`.
* @return New string with the expanded and merged variable.
*/
static char *ft_join_env(t_token *tok, int j, char **tmp, t_minishell *boogeyman)
{
	char *value;

	value = ft_expand_variable(tmp[0], boogeyman);
	tmp[2] = ft_strjoin(tmp[1], value);
	free(value);
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
* @brief Expands an environment variable into a token string.
*
* Looks in `tok->str` for an environment variable, expands it, and rebuilds the string.
* If `check_w_cards` is true, performs re-kenning after expansion.
*
* @param curr Current item in the token list.
* @param i Index of the `$` character in `tok->str` to expand the variable.
* @param check_w_cards Flag indicating whether to re-kennize.
* @param boogeyman `t_minishell` structure with the `envp` environment.
*/
void ft_expand_env(t_list *curr, int *i, int check_w_cards, t_minishell *boogeyman)
{
	int	j;
	t_token *tok;
	char *tmp[3];
	j = *i;
	tok = curr->data;
	while (tok->str[j + 1] && !ft_is_reserved_char(tok->str[j + 1])
		&& tok->str[j + 1] != '"' && tok->str[j + 1] != '\'' && tok->str[j + 1] != '*'
		&& !ft_isspace(tok->str[j + 1]))
		j++;
	tmp[0] = ft_substr(tok->str, *i + 1, j - *i);
	if (!*tmp[0])
	{
		free(tmp[0]);
		(*i)++;
		return ;
	}
	tmp[1] = ft_substr(tok->str, 0, *i);
	tok->str = ft_join_env(tok, j, tmp, boogeyman);
	if (check_w_cards)
		retokenize(curr, E_EXP_ARG, *i, (int []){*i
			+ ft_strlen(get_value_from_env(boogeyman->envp, tmp[0], NULL))});

	*i = *i + ft_strlen(get_value_from_env(boogeyman->envp, tmp[0], NULL));
	free_cmd_token(tok);
	((t_token *)curr->data)->type = E_EXP_ARG;
}
