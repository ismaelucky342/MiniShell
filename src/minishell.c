/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:20:18 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 17:33:04 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int	g_exit;

static void	get_command_str(t_minishell *boogeyman)
{
	char	*tmp;
	char	*res;

	ft_set_echo(1);
	rl_replace_line("", 0);
	rl_on_new_line();
	tmp = readline(boogeyman->ft_prompt);
	if (!tmp)
	{
		boogeyman->eof = 1;
		return ;
	}
	res = ft_strtrim(tmp, " \v\t\n\r");
	free(tmp);
	if (res && *res)
	{
		ft_add_history(res, boogeyman);
		boogeyman->cmd_tree = ft_calloc(1, sizeof(t_ast_tree));
		if (!boogeyman->cmd_tree)
			ft_memory_error(boogeyman);
		boogeyman->cmd_tree->cmd_str = res;
		return ;
	}
	if (res)
		free(res);
}

/*void	leaks(void)
{
	system("leaks minishell");
} */

void	ft_setsigint(t_minishell *boogeyman)
{
	ft_env_build(boogeyman, "?=130");
	g_exit = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	m_boogeyman;

	rl_initialize();
	init_minishell(&m_boogeyman, envp, argc, argv);
	while (1)
	{
		get_command_str(&m_boogeyman);
		if (g_exit == 3)
			ft_setsigint(&m_boogeyman);
		if (m_boogeyman.cmd_tree && !m_boogeyman.eof)
		{
			if (ft_check_heredoc(&m_boogeyman))
				//expand_execute(m_boogeyman.cmd_tree, &m_boogeyman);
				//print_ast_tree(m_boogeyman.cmd_tree);
			m_boogeyman.cmd_tree = ft_free_ast_tree(m_boogeyman.cmd_tree);
		}
		else if (m_boogeyman.eof)
			ft_exit_msg(0, &m_boogeyman, 1);
	}
	return (OK);
}
