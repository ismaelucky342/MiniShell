/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:20:18 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/04 16:17:58 by dgomez-l         ###   ########.fr       */
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
	t_minishell	boogeyman;

	rl_initialize();
	init_minishell(&boogeyman, envp, argc, argv);
	while (1)
	{
		get_command_str(&boogeyman);
		if (g_exit == 3)
			ft_setsigint(&boogeyman);
		if (boogeyman.cmd_tree && !boogeyman.eof)
		{
			if (ft_check_heredoc(&boogeyman))
				ft_execution(boogeyman.cmd_tree, &boogeyman);
				//expand_execute(boogeyman.cmd_tree, &boogeyman);
				//print_ast_tree(boogeyman.cmd_tree);
			boogeyman.cmd_tree = ft_free_ast_tree(boogeyman.cmd_tree);
		}
		else if (boogeyman.eof)
			ft_exit_msg(0, &boogeyman, 1);
	}
	return (OK);
}
