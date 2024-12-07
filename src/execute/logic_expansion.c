/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:20:15 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/12/07 13:17:59 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * if_mask - Determines the type of logical operator in the given string.
 * @str: The input string to check for logical operators.
 * @last: The index in the string to check for logical operators.
 *
 * Return: M_AND_OP if '&&' is found, M_OR_OP if '||' is found,
 *         M_WAIT if ';' is found, 0 otherwise.
 */
int	if_mask(char *str, int last)
{
	if (str[last] == '&' && str[last + 1] == '&')
		return (M_AND_OP);
	else if (str[last] == '|' && str[last + 1] == '|')
		return (M_OR_OP);
	else if (str[last] == ';')
		return (M_WAIT);
	return (0);
}

/**
 * expand_execute - Expands and executes the AST tree node.
 * @tree_node: The current AST tree node to expand and execute.
 * @boogeyman: The minishell context containing env and execution state.
 *
 * This function attempts to expand logical expressions in the AST tree node.
 * It recursively processes the left and right child nodes based on the logical
 * operator and executes the command list if no logical operator is found.
 *
 * Return: The exit code of the executed command or logical expression.
 */
int	expand_execute(t_ast_tree *tree_node, t_mini *boogeyman)
{
	char	*keyval;
	char	*nbrstr;

	boogeyman->cont = 1;
	if (logic_expansion(tree_node))
		return (ft_expansion_error(tree_node), ft_printexit(2, boogeyman, 1),
			2);
	if (tree_node->left)
		tree_node->exit_code = expand_execute(tree_node->left, boogeyman);
	if (tree_node->right)
		if (((tree_node->exit_code == 0 && tree_node->is_logic == M_AND_OP)
				|| (tree_node->exit_code != 0 && tree_node->is_logic == M_OR_OP)
				|| (tree_node->is_logic == M_WAIT)) && boogeyman->cont)
			tree_node->exit_code = expand_execute(tree_node->right, boogeyman);
	if (!tree_node->is_logic)
		tree_node->exit_code = ft_parse_and_exec_monitor(tree_node, boogeyman);
	nbrstr = ft_itoa(tree_node->exit_code);
	keyval = ft_strjoin("?=", nbrstr);
	ft_add_to_env(boogeyman, keyval);
	return (free(keyval), free(nbrstr), tree_node->exit_code);
}

/**
 * ft_remove_brackets - Removes outer brackets from the given string.
 * @str: The input string from which to remove outer brackets.
 *
 * This function duplicates the input string and removes outer brackets
 * until no more removable brackets are found.
 *
 * Return: A new string with outer brackets removed.
 */
char	*ft_remove_brackets(char *str)
{
	char	*res;

	res = ft_strdup(str);
	while (!get_log_expandible(res) && ft_has_brackets(res))
		ft_remove_outer_brackets(res);
	return (res);
}

/**
 * logic_expansion - Expands logical expressions in the AST tree node.
 * @tree_node: The current AST tree node to expand.
 *
 * This function removes outer brackets from the command string and checks
 * if it contains logical operators. If logical operators are found, it splits
 * the command string into left and right tokens and assigns them to the left
 * and right child nodes of the AST tree node.
 *
 * Return: 2 if there is an error in splitting the command string, 0 otherwise.
 */
int	logic_expansion(t_ast_tree *tree_node)
{
	char	*str;

	str = ft_remove_brackets(tree_node->cmd_str);
	tree_node->is_logic = get_log_expandible(str);
	if (tree_node->is_logic)
	{
		tree_node->left = ft_calloc(1, sizeof(t_ast_tree));
		tree_node->left->cmd_str = ft_get_left_token(str);
		tree_node->right = ft_calloc(1, sizeof(t_ast_tree));
		tree_node->right->cmd_str = ft_get_right_token(str);
		if ((!tree_node->left->cmd_str || !(*tree_node->left->cmd_str))
			|| (!tree_node->right->cmd_str || !(*tree_node->right->cmd_str)))
			return (2);
	}
	free(str);
	return (0);
}
