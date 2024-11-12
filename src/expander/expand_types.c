/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:58:02 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/12 11:27:32 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
* @brief Expands environment variables within a double-quoted string.
*
* Removes double quotes from the current token and expands any environment variables
* present in the string. Replaces the variable with its corresponding value in the minishell environment.
*
* @param curr Node in the list containing the token to expand.
* @param i Pointer to the current index in the token string.
* @param boogeyman Minishell context containing environment information and other data
* needed for expansion.
*/
void double_quote_expand(t_list *curr, int *i, t_minishell *boogeyman)
{
	int	j;
	t_token *tok;

	j = *i;
	tok = curr->data;
	while (tok->str[j])
	{
		tok->str[j] = tok->str[j + 1];
		++j;
	}
	while (tok->str[*i] != '"' && tok->str[*i])
	{
		if (tok->str[*i] == '$')
			ft_expand_env(curr, i, 0, boogeyman);
		else
			++(*i);
	}
	j = *i;
	while (tok->str[j] && tok->str[j + 1])
	{
		tok->str[j] = tok->str[j + 1];
		++j;
	}
	tok->str[j] = '\0';
}

/**
* @brief Removes single quotes from a string and leaves its contents unexpanded.
*
* Single quotes indicate that any content within them should not be expanded.
* This function simply removes the single quotes from the token.
*
* @param curr Node in the list containing the token to process.
* @param i Pointer to the current index in the token string.
*/
void single_quote_expand(t_list *curr, int *i)
{
	int	j;
	t_token *tok;

	j = *i;
	tok = curr->data;
	while (tok->str[j])
	{
		tok->str[j] = tok->str[j + 1];
		++j;
	}
	while (tok->str[*i] != '\'' && tok->str[*i])
		++(*i);
	j = *i;
	while (tok->str[j] && tok->str[j + 1])
	{
		tok->str[j] = tok->str[j + 1];
		++j;
	}
	tok->str[j] = '\0';
}

/**
* @brief Expands all strings in a list of tokens.
*
* Iterates through each node in the list and expands the contents of each token if necessary.
* The expansion includes handling of environment variables, single quotes, double quotes,
* and wildcards.
*
* @param list List of tokens to expand.
* @param boogeyman Minishell context containing environment information
* and other data needed for expansion.
* @return OK on success.
*/
int ft_list_expand(t_list *list, t_minishell *boogeyman)
{
	while (list)
	{
		if (((t_token *)list->data)->type == ARG)
			list_expand(list, boogeyman);
		else if (((t_token *)list->data)->type == E_EXP_ARG)
			list_expand(list, boogeyman);
		else
			list = list->next;
	}
	return (OK);
}

/**
* @brief Expands a token based on its type and content.
*
* Depending on the token's type, performs appropriate expansion for single quotes,
* double quotes, environment variables, or wildcards. The expansion transforms
* the token and updates its type if necessary.
*
* @param curr Node in the list containing the token to expand.
* @param boogeyman Minishell context containing environment information
* and other data needed for expansion.
*/
void list_expand(t_list *curr, t_minishell *boogeyman)
{
	t_token *tok;
	int	i;
	int	pre_type;

	tok = curr->data;
	i = 0;
	pre_type = tok->type;
	while (i < (int)ft_strlen(tok->str))
	{
		if (tok->str[i] == '\'' && pre_type == ARG)
			single_quote_expand(curr, &i);
		else if (tok->str[i] == '"' && pre_type == ARG)
			double_quote_expand(curr, &i, boogeyman);
		else if (tok->str[i] == '*' && pre_type == E_EXP_ARG)
			return (wildcard_expand(curr, &i), (void)0);
		else if (tok->str[i] == '$' && pre_type == ARG)
			ft_expand_env(curr, &i, 1, boogeyman);
		else
			++i;
		tok = curr->data;
	}
	if (pre_type == E_EXP_ARG)
		tok->type = W_EXP_ARG;
	if (pre_type == ARG)
		tok->type = E_EXP_ARG;
}
