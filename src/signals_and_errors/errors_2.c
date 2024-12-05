/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:31:34 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 13:00:08 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handles cleanup and exits the shell.
 *
 * This function closes the history file descriptor, frees allocated memory for
 * the custom prompt and environment variables, and also frees the command 
 * tree if present. Finally, it exits the program with the specified exit code.
 *
 * @param exit_code The exit code to be returned by the program.
 * @param boogeyman A pointer to the minishell structure that contains necessary data.
 * @param print A flag that determines whether to print "exit" to STDERR.
 */
void	ft_printexit(int exit_code, t_minishell *boogeyman, char print) 
{
	if (print)
		ft_putendl_fd("exit", STDERR_FILENO);
	close(boogeyman->history_fd);
	free(boogeyman->custom_prompt);
	ft_free_array(boogeyman->envp);
	if (boogeyman->cmd_tree)
		ft_free_cmdtree(boogeyman->cmd_tree);
	exit(exit_code);
}

/**
 * @brief Retrieves the current working directory as a string.
 *
 * This function uses `getcwd` to get the current working directory, 
 * handling any errors that may occur during the operation.
 *
 * @return A string representing the current working directory, or NULL if an error occurs.
 */
char	*cwd_str_status(void)
{
	void	*nullable;
	char	cwd[256];

	nullable = getcwd(cwd, sizeof(cwd));
	if (!nullable)
	{
		perror("MiniShell: update cwd error");
		return (NULL);
	}
	return (ft_strdup(cwd));
}
