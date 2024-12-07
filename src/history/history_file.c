/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:18:19 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/07 22:30:49 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Initializes the history file for the minishell.
 *
 * This function attempts to retrieve the user's home directory from the env
 * variables. If the home directory is found,
	it appends the history file base name
 * to it and opens the file with read and write permissions.
 * If the home directory is not found or if there is an error during memory
		allocation, appropriate error handling is performed.
 *
 * @param boogeyman A pointer to the minishell structure containing env
 *                  variables and fds.
 */
void	ft_init_history_file(t_mini *boogeyman)
{
	char	*home;

	home = ft_get_from_env(boogeyman->envp, "HOME", NULL);
	if (!*home)
	{
		boogeyman->history_fd = -1;
		ft_putendl_fd(HIST_ERROR_MSG, STDERR_FILENO);
		return ;
	}
	home = ft_strjoin(home, HIST_TMP_BASE);
	if (!home)
		ft_memory_err_exit(boogeyman);
	boogeyman->history_fd = open(home, O_CREAT | O_RDWR, 0644);
	freedom((void **)&home);
}
