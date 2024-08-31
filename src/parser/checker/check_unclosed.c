/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:53:58 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/08/31 16:54:01 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*check_unclosed(char *command, t_exec *exec)
{
	char	*tmp;

	while (check_quotess(command) == -1)
	{
		tmp = ft_strjoin(command, "\n");
		free(command);
		command = ft_strjoin_free(tmp, readline("> "));
		if (check_quotess(command) != -1)
			add_history(command);
	}

	if (check_quotess(command) == -2)
	{
		ft_putstr_fd("minishell: unclosed parentesisthesis\n", 2);
		exec->exit_status = 2;
		free(command);
		return (NULL);
	}
	return (command);
}
