/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:31:36 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/12/05 12:30:17 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/**
 * @brief Delimits comparison for brackets and quotes in a string.
 *
 * This function increments or decrements the bracket counter based on the
 * character at the current position in the string. If a single quote is
 * encountered, it calls the state_quote_delimiter function.
 *
 * @param str The input string to be processed.
 * @param j Pointer to the current position in the string.
 * @param b_ctr Pointer to the bracket counter.
 */

static void	delimit_cmp(char *str, int *j, int *b_ctr)
{
	if (str[*j] == '(')
		++(*b_ctr);
	else if (str[*j] == ')')
		--(*b_ctr);
	else if (str[*j] == '\'')
		state_quote_delimiter(str, j, '\'');
}


/**
 * @brief Removes outer brackets from a string.
 *
 * This function iterates through the input string and removes the outermost
 * brackets if they are present. It also handles quoted substrings by calling
 * the state_quote_delimiter function.
 *
 * @param str The input string from which outer brackets are to be removed.
 */
void	ft_remove_outer_brackets(char *str)
{
	int	i;
	int	j;
	int	b_ctr;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '(')
		{
			j = i;
			b_ctr = 1;
			while (b_ctr && str[++j])
				delimit_cmp(str, &j, &b_ctr);
			while (str[++j - 1])
				str[j - 1] = str[j];
			while (str[++i - 1])
				str[i - 1] = str[i];
			return ;
		}
		else if (str[i] == '\'')
			state_quote_delimiter(str, &i, '\'');
	}
}

/**
 * @brief Checks if a string is logically expandable.
 *
 * This function checks if the input string contains logical operators (&&, ||, ;)
 * or brackets that make it logically expandable. It also handles quoted substrings
 * by calling the state_quote_delimiter function.
 *
 * @param str The input string to be checked.
 * @return Returns 0 if the string is not logically expandable, else returns a positive value.
 */

int	get_log_expandible(char *str)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			state_quote_delimiter(str, &i, str[i]);
			if (str[i] == '\'' || str[i] == '\"')
				++i;
		}
		if ((str[i] == '&' && str[i + 1] == '&')
			|| (str[i] == '|' && str[i + 1] == '|') || (str[i] == ';'))
			last = i++;
		else if (str[i] == '(')
			ft_brackets(str, &i);
		else if (str[i])
			++i;
	}
	return (if_mask(str, last));
}

/**
 * @brief Checks if a string contains brackets.
 *
 * This function iterates through the input string and checks if it contains any
 * brackets. It also handles quoted substrings by calling the state_quote_delimiter function.
 *
 * @param str The input string to be checked.
 * @return Returns the bracket character if found, otherwise returns 0.
 */
char	ft_has_brackets(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			state_quote_delimiter(str, &i, '\'');
		else if (str[i] == '"')
			state_quote_delimiter(str, &i, '"');
		else if (str[i] == '(')
			return (str[i]);
	}
	return (0);
}


/**
 * @brief Prints an expansion error message.
 *
 * This function prints a syntax error message to the standard error output
 * based on the logical operator present in the tree node.
 *
 * @param tree_node The AST tree node containing the logical operator.
 */
void	ft_expansion_error(t_ast_tree *tree_node)
{
	ft_putstr_fd("MiniShell: syntax error near '", STDERR_FILENO);
	if (tree_node->is_logic == M_AND_OP)
		ft_putstr_fd("&&", STDERR_FILENO);
	if (tree_node->is_logic == M_OR_OP)
		ft_putstr_fd("||", STDERR_FILENO);
	if (tree_node->is_logic == M_WAIT)
		ft_putstr_fd(";", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}
