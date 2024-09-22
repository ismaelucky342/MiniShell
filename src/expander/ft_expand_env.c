/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:51:48 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:45:13 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_expand_variable(char *var_name, t_minishell *sack)
{
	return (get_value_from_env(sack->envp, var_name, NULL));
}

static char	*ft_join_env(t_token *tok, int j, char **tmp, t_minishell *sack)
{
	char	*value;

	value = ft_expand_variable(tmp[0], sack);
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

void	ft_expand_env(t_list *curr, int *i, int check_w_cards,
		t_minishell *sack)
{
	int		j;
	t_token	*tok;
	char	*tmp[3];

	j = *i;
	tok = curr->data;
	while (tok->str[j + 1] && !ft_is_reserved_char(tok->str[j + 1])
		&& tok->str[j + 1] != '"' && tok->str[j + 1] != '\'' && tok->str[j
			+ 1] != '*' && !ft_isspace(tok->str[j + 1]))
		j++;
	tmp[0] = ft_substr(tok->str, *i + 1, j - *i);
	if (!*tmp[0])
	{
		free(tmp[0]);
		(*i)++;
		return ;
	}
	tmp[1] = ft_substr(tok->str, 0, *i);
	tok->str = ft_join_env(tok, j, tmp, sack);
	if (check_w_cards)
		retokenize(curr, E_EXP_ARG, *i, (int []){*i
			+ ft_strlen(get_value_from_env(sack->envp, tmp[0], NULL))});
	*i = *i + ft_strlen(get_value_from_env(sack->envp, tmp[0], NULL));
	free_cmd_token(tok);
	((t_token *)curr->data)->type = E_EXP_ARG;
}
