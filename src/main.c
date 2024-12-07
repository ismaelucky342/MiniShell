/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:16:41 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/07 22:30:49 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_is_exec;

/*
	Tries to read a line, with EOF protection
	Also trims spaces, and stores the str inside a cmd_tree
	node and in the history
*/
static void	get_command_str(t_mini *boogeyman)
{
	char	*tmp;
	char	*res;

	ft_set_echo(1);
	rl_replace_line("", 0);
	rl_on_new_line();
	tmp = readline(boogeyman->custom_prompt);
	if (!tmp)
	{
		boogeyman->eof = 1;
		return ;
	}
	res = ft_strtrim(tmp, " \v\t\n\r");
	freedom((void **)&tmp);
	if (res && *res)
	{
		ft_add_history(res, boogeyman);
		boogeyman->cmd_tree = ft_calloc(1, sizeof(t_ast_tree));
		if (!boogeyman->cmd_tree)
			ft_memory_err_exit(boogeyman);
		boogeyman->cmd_tree->cmd_str = res;
		return ;
	}
	if (res)
		freedom((void **)&res);
}

/* void	leaks(void)
{
	system("leaks minishell");
} */
void	ft_setsigint(t_mini *boogeyman)
{
	boogeyman->rvalue = 130;
	g_is_exec = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_mini		m_boogeyman;

	rl_initialize();
	init(&m_boogeyman, envp, argc, argv);
	while (1)
	{
		get_command_str(&m_boogeyman);
		if (g_is_exec == 3)
			ft_setsigint(&m_boogeyman);
		if (m_boogeyman.cmd_tree && !m_boogeyman.eof)
		{
			if (ft_check_syntax_heredoc(&m_boogeyman))
				expand_execute(m_boogeyman.cmd_tree, &m_boogeyman);
			m_boogeyman.cmd_tree = ft_free_cmdtree(m_boogeyman.cmd_tree);
		}
		else if (m_boogeyman.eof)
			ft_printexit(0, &m_boogeyman, 1);
	}
	return (0);
}
