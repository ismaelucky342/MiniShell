/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:22:27 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/08/31 15:22:29 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	parse_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDIN_FILENO, "^C\n", 3);
		if (!DEBUG)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	if (signal == SIGQUIT)
		return ;
}
