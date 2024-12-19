/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:59:26 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/18 19:16:34 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * expand_list - Expands tokens in a linked list node based on their type.
 * @curr: Pointer to the current node in the linked list.
 * @boogeyman: Pointer to the minishell structure containing env
		variables.
 *
 * This function iterates through the string in the token of the current node
 * and expands it based on the character encountered and the token type.
 * It handles single quotes, double quotes, wildcards,
	and env variables.
 * The token type is updated accordingly after expansion.
 */
void	expand_list_tokens(t_list *curr, t_mini *boogeyman)
{
	t_token	*tok;
	int		i;
	int		pre_type;

	tok = curr->content;
	i = 0;
	pre_type = tok->type;
	while (i < (int)ft_strlen(tok->str))
	{
		if (tok->str[i] == '\'' && pre_type == ARG)
			single_quote_expander(curr, &i);
		else if (tok->str[i] == '"' && pre_type == ARG)
			double_quote_expander(curr, &i, boogeyman);
		else if (tok->str[i] == '$' && pre_type == ARG)
			env_expander(curr, &i, 1, boogeyman);
		else if (tok->str[i] == '*' && pre_type == ARG)
			return (wildcard_expander(curr, &i), (void)0);
		else
			++i;
		tok = curr->content;
	}
	if (pre_type == E_EXP_ARG)
		tok->type = W_EXP_ARG;
	if (pre_type == ARG)
		tok->type = E_EXP_ARG;
}

/**
 * @brief Expands env variables in a list of tokens.
 *
 * This function iterates through a list of tokens and expands any env
 * variables found in tokens of type ARG or E_EXP_ARG using the
		provided minishell
 * context.
 *
 * @param list The list of tokens to be expanded.
 * @param boogeyman The minishell context containing env variables
		and other settings.
 * @return Always returns 0.
 */
int	ft_expand_str_list(t_list *list, t_mini *boogeyman)
{
	while (list)
	{
		if (((t_token *)list->content)->type == ARG)
			expand_list_tokens(list, boogeyman);
		else if (((t_token *)list->content)->type == E_EXP_ARG)
			expand_list_tokens(list, boogeyman);
		else
			list = list->next;
	}
	return (0);
}
