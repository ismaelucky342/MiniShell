/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:14:15 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/08/31 17:14:16 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_print_token_list(t_token *token_list)
{
	t_token	*holder;

	holder = token_list;
	while (holder)
	{
		printf("token type: %d\n", holder->token_type);
		printf("token value: %s\n\n", holder->value);
		holder = holder->next;
	}
	return ;
}

void	ft_print_tree(t_ast *ast_tree)
{
	if (!ast_tree->left)
	{
		printf("THE TREE: ~~~~~~~~~~~~~~~~~~~~\n");
		if (ast_tree->value)
		{
			ft_putstr_fd("left cmd:", 1);
			ft_putstr_array(ast_tree->value);
		}
		return ;
	}
	if (ast_tree->left)
		ft_print_tree(ast_tree->left);
	if (ast_tree->right->value)
	{
		ft_putstr_fd("right cmd:", 1);
		ft_putstr_array(ast_tree->right->value);
	}
}

void	ft_test(t_token *token_list, t_ast *ast, t_hashtable *env_hashtable)
{
	char	*str[4];

	ft_print_token_list(token_list);
	ft_print_tree(ast);
	str[0] = "cd";
	str[2] = "abc";
	str[1] = "123";
	str[3] = 0;
	if (ast->left && ast->right)
	{
		env_hashtable = ft_export(ast_tree->left->value, env_hashtable);
		printf("left value : %s\n", ast->left->value[1]);
		printf("right value : %s\n", ast->right->value[1]);
		env_hashtable = ft_unset(ast->right->value, env_hashtable);
		ft_cd(str, &env_hashtable);
		ft_pwd();
	}
}
