/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:31:34 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 17:23:15 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handles cleanup and exits the shell.
 *
 * This function closes the history fd, frees allocated memory for
 * the custom prompt and env variables, and also frees the command 
 * tree if present. Finally, it exits the program with the specified exit code.
 *
 * @param exit_code The exit code to be returned by the program.
 * @param boogeyman A pointer to the minishell structure that contains
		necessary data.
 * @param print A flag that determines whether to print "exit" to STDERR.
 */
void	ft_printexit(int exit_code, t_mini *boogeyman, char print)
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
 * @return A string representing the current working directory,
	or NULL if an error occurs.
 */
char	*cwd_str_status(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("MiniShell: update cwd error");
		return (NULL);
	}
	return (cwd);
}
