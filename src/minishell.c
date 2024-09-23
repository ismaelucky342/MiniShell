/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:20:18 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/23 10:48:41 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit;

static void	get_command_str(t_minishell *sack)
{
	char	*tmp;
	char	*res;

	ft_set_echo(1);
	rl_replace_line("", 0);
	rl_on_new_line();
	tmp = readline(sack->ft_prompt);
	if (!tmp)
	{
		sack->eof = 1;
		return ;
	}
	res = ft_strtrim(tmp, " \v\t\n\r");
	free(tmp);
	if (res && *res)
	{
		ft_add_history(res, sack);
		sack->cmd_tree = ft_calloc(1, sizeof(t_ast_tree));
		if (!sack->cmd_tree)
			ft_memory_error(sack);
		sack->cmd_tree->cmd_str = res;
		return ;
	}
	if (res)
		free(res);
}

/*void	leaks(void)
{
	system("leaks minishell");
} */

void	ft_setsigint(t_minishell *sack)
{
	ft_env_build(sack, "?=130");
	g_exit = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	m_sack;

	rl_initialize();
	init_minishell(&m_sack, envp, argc, argv);
	while (1)
	{
		get_command_str(&m_sack);
		if (g_exit == 3)
			ft_setsigint(&m_sack);
		if (m_sack.cmd_tree && !m_sack.eof)
		{
			if (ft_check_heredoc(&m_sack))
				//expand_execute(m_sack.cmd_tree, &m_sack);
				//print_ast_tree(m_sack.cmd_tree);
			m_sack.cmd_tree = ft_free_ast_tree(m_sack.cmd_tree);
		}
		else if (m_sack.eof)
			ft_exit_msg(0, &m_sack, 1);
	}
	return (0);
}
