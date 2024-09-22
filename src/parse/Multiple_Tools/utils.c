/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:17:35 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 12:11:24 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_exit_msg(int exit_key, t_minishell *sack, char print)
{
	if (print)
		ft_putendl_fd("exit", STDERR_FILENO);
	close(sack->history_fd);
	free(sack->ft_prompt);
	ft_array_free(sack->envp);
	if (sack->cmd_tree)
		ft_free_ast_tree(sack->cmd_tree);
	exit (exit_key);
}

char	*get_cwd_str(void)
{
	void	*nullable;
	char	cwd[256];

	nullable = getcwd(cwd, sizeof(cwd));
	if (!nullable)
	{
		perror("Minishell: update cwd error");
		return (NULL);
	}
	return (ft_strdup(cwd));
}
