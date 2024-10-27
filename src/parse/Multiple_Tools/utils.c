/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:17:35 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 17:30:35 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_exit_msg(int exit_key, t_minishell *boogeyman, char print)
{
	if (print)
		ft_putendl_fd("exit", STDERR_FILENO);
	close(boogeyman->history_fd);
	free(boogeyman->ft_prompt);
	ft_array_free(boogeyman->envp);
	if (boogeyman->cmd_tree)
		ft_free_ast_tree(boogeyman->cmd_tree);
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
