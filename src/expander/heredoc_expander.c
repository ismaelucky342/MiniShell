/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:19:00 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/04 15:40:13 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
* @brief Generates a unique name for a temporary heredoc file.
*
* This function takes an index, converts it to a string, and concatenates it
* with the base `H_DOC_TMP_BASE` to create a temporary file name.
*
* @param index Index to use to generate a unique name.
* @return String containing the generated temporary file name.
*/
static char *generate_tmp_filename(int index)
{
	char *tmp;
	char *name;

	tmp = ft_itoa(index);
	if (!tmp)
		return (NULL);
	name = ft_strjoin(H_DOC_TMP_BASE, tmp);
	free(tmp);
	return (name);
}

/**
* @brief Gets a temporary file name available for heredoc.
*
* This function attempts to create unique temporary file names in a range of 1 to 1000.
* If a name does not exist (determined using `access`), it returns that name.
*
* @return Available file name, or `NULL` if no names are available.
*/
char *get_tmp_filename(void)
{
	char *name;
	int	i;

	i = 1;
	while (i <= 1000)
	{
		name = generate_tmp_filename(i);
		if (!name)
			return (NULL);
		if (access(name, F_OK) != 0)
			return (name);
		free(name);
		i++;
	}
	return (NULL);
}

/**
* @brief Print an error in the heredoc and terminate execution.
*
* Call `perror` to print the error associated with `tok->name`,
* release `tok->name` and terminate execution with `exit(1)`.
*
* @param tok Redirection token containing the name of the heredoc file.
*/
static void handle_heredoc_error(t_redir_token *tok)
{
	perror(tok->name);
	free(tok->name);
	exit(1);
}

/**
* @brief Creates a temporary heredoc file and writes its expanded contents.
*
* Opens the temporary file named in `tok->name`, reads lines from
* `o_fd`, expands variables using `ft_expand`, and writes each expanded line to the file.
*
* @param o_fd File descriptor to read the lines from the heredoc.
* @param tok Redirection token containing the name of the heredoc file.
* @param envp Environment to expand variables in the heredoc lines.
* @return File descriptor of the temporary file, or -1 on error.
*/
static int open_and_write_heredoc(int o_fd, t_redir_token *tok, char **envp)
{
	int	fd;
	char *line;
	char *exp;

	unlink(tok->name);
	free(tok->name);
	tok->name = get_tmp_filename();
	if (!tok->name)
	{
		ft_putendl_fd("No heredoc tmp file available!", STDERR_FILENO);
		return (exit(1), -1);
	}
	fd = open(tok->name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		handle_heredoc_error(tok);
	line = get_next_line(o_fd);
	while (line)
	{
		exp = ft_expand(line, envp, 1);
		ft_putstr_fd(exp, fd);
		free(line);
		free(exp);
		line = get_next_line(o_fd);
	}
	return (fd);
}

/**
* @brief Expands the heredoc and writes it to a temporary file.
*
* Calls `open_and_write_heredoc` to perform the expansion and writing.
*
* @param o_fd File descriptor to read the heredoc lines into.
* @param tok Redirection token containing the name of the heredoc file.
* @param envp Environment to expand variables in the heredoc lines into.
* @return File descriptor of the temporary file, or -1 on error.
*/
int ft_expand_heredoc(int o_fd, t_redir_token *tok, char **envp)
{
	return (open_and_write_heredoc(o_fd, tok, envp));
}
