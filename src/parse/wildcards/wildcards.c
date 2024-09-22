/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:52:24 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:05:18 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_is_wildcard(char *f_name, char *regex)
{
	int	cont[2];

	ft_memset(cont, 0, sizeof(int) * 2);
	if (!ft_strncmp(".", f_name, 2) || !ft_strncmp("..", f_name, 3)
		|| (f_name[0] == '.' && regex[0] != '.'))
		return (0);
	while (f_name[cont[0]] && regex[cont[1]])
	{
		if (regex[cont[1]] == '*')
		{
			while (regex[cont[1]] == '*')
				++cont[1];
			while (f_name[cont[0]] && f_name[cont[0]] != regex[cont[1]])
				++cont[0];
		}
		if (f_name[cont[0]] != regex[cont[1]])
			return (0);
		handle_wildcard(cont, f_name, regex);
	}
	if (!regex_iterator(regex, f_name, &cont[1], cont[0]))
		return (0);
	return (1);
}

char	*ft_wildcards(char *regex)
{
	DIR				*dir_ptr;
	struct dirent	*directory;
	char			*file_list;
	char			*tmp;

	get_files(&dir_ptr, &directory);
	file_list = ft_strdup("");
	if (!directory || !file_list)
		return (NULL);
	while (directory)
	{
		if (ft_is_wildcard(directory->d_name, regex))
		{
			tmp = ft_strjoin(file_list, directory->d_name);
			free(file_list);
			file_list = ft_strjoin(tmp, " ");
			free(tmp);
		}
		directory = readdir(dir_ptr);
	}
	if (!file_list[0])
		return (free(file_list), closedir(dir_ptr), NULL);
	tmp = ft_strtrim(file_list, " \n\t\r\v");
	free(file_list);
	return (closedir(dir_ptr), tmp);
}
