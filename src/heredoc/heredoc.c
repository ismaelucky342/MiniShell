/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:50:36 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 13:17:56 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_is_exec;

/**
 * Generates a temporary filename for the heredoc.
 *
 * This function generates a unique temporary filename by appending an integer
 * to a base string (H_DOC_TMP_BASE). It checks if the file already exists and
 * returns the first available filename.
 *
 * @return A pointer to the generated filename string, or NULL if no available
 *         filename was found within the limit.
 */
char	*tmp_filename(void)
{
	char	*name;
	char	*tmp;
	int		i;

	i = 0;
	while (++i <= 1000)
	{
		tmp = ft_itoa(i);
		name = ft_strjoin(H_DOC_TMP_BASE, tmp);
		free(tmp);
		if (access(name, F_OK) != 0)
			return (name);
		free(name);
	}
	return (NULL);
}

/**
 * Extracts the delimiter from the input string.
 *
 * This function extracts the delimiter from the input string, starting from
 * the current position. It skips any leading whitespace and handles quoted
 * delimiters. The extracted delimiter is returned, and the input string is
 * modified to replace the delimiter with a new name.
 *
 * @param str The input string.
 * @param i The current position in the input string.
 * @param new_name The new name to replace the delimiter in the input string.
 * @return A pointer to the extracted delimiter string, or NULL if no delimiter
 *         was found.
 */

static char	*delimiter(char **str, int *i, char *new_name)
{
	int		j;
	char	*delim;
	char	*tmp;
	char	*tmp2;

	while (ft_isspace((*str)[(*i)]))
		*i += 1;
	j = *i;
	while ((*str)[j] && !ft_isspace((*str)[j]) && !ft_isreserved((*str)[j])
		&& (*str)[j] != '(' && (*str)[j] != ')')
	{
		if ((*str)[j] == '\'' || (*str)[j] == '"')
			state_quote_delimiter(*str, &j, (*str)[j]);
		else
			++j;
	}
	if (j == *i)
		return (NULL);
	delim = ft_substr(*str, *i, j - *i);
	tmp = ft_substr(*str, 0, *i);
	tmp2 = ft_strjoin(tmp, new_name);
	delim_subs(str, j, tmp, tmp2);
	return (*i += ft_strlen(new_name), delim);
}


/**
 * Auxiliary function for handling heredoc.
 *
 * This function generates a temporary filename, opens the file, and extracts
 * the delimiter from the input string. It returns the file descriptor of the
 * opened file.
 *
 * @param str The input string.
 * @param i The current position in the input string.
 * @param delim A pointer to store the extracted delimiter.
 * @param f_name A pointer to store the generated filename.
 * @return The file descriptor of the opened file, or -1 on error.
 */
static int	aux_heredoc(char **str, int *i, char **delim, char **f_name)
{
	int		fd;

	*f_name = tmp_filename();
	if (!*f_name)
		return (ft_putendl_fd("No heredoc tmp file available!", 2),
			exit(1), -1);
	fd = open(*f_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(*f_name), free(*f_name), exit(1), -1);
	*i += 2;
	*delim = delimiter(str, i, *f_name);
	if (!*delim)
	{
		ft_close(fd);
		return (-1);
	}
	return (fd);
}

/**
 * Handles the heredoc functionality.
 *
 * This function sets up the heredoc by calling the auxiliary function to
 * generate the filename and extract the delimiter. It then forks a child
 * process to handle the heredoc input, displaying a prompt and reading lines
 * until the delimiter is encountered.
 *
 * @param str The input string.
 * @param i The current position in the input string.
 * @param f_name A pointer to store the generated filename.
 * @return 0 on success, or 1 on error.
 */
int	ft_heredoc(char **str, int *i, char **f_name)
{
	int		fd;
	char	*delim;
	char	*line;
	char	*prompt;
	int		pid;

	fd = aux_heredoc(str, i, &delim, f_name);
	ft_str_unquote(delim);
	if (fd == -1 || !g_is_exec)
		return (free(delim), 1);
	pid = fork();
	if (pid < 0)
		return (free(delim), 1);
	if (pid)
		return (free(delim), 0);
	signal(SIGINT, SIG_DFL);
	line = ft_strjoin("here_doc (", delim);
	prompt = ft_strjoin(line, ") > ");
	free(line);
	line = readline(prompt);
	heredoc_monitor(&line, prompt, delim, &fd);
	if (line)
		free(line);
	return (free(delim), free(prompt),
		ft_close(fd), free(*f_name), exit(0), 0);
}
