/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:43:30 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/10 20:57:50 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_is_wildcard(char *f_name, char *wc)
{
	int	cont[2];

	ft_memset(cont, 0, sizeof(int) * 2);
	if (!ft_strncmp(".", f_name, 2) || !ft_strncmp("..", f_name, 3)
		|| (f_name[0] == '.' && wc[0] != '.'))
		return (0);
	while (f_name[cont[0]] && wc[cont[1]])
	{
		if (wc[cont[1]] == '*')
		{
			while (wc[cont[1]] == '*')
				++cont[1];
			while (f_name[cont[0]] && f_name[cont[0]] != wc[cont[1]])
				++cont[0];
		}
		if (f_name[cont[0]] != wc[cont[1]])
			return (0);
		wildcard_process(cont, f_name, wc);
	}
	if (!wc_iterator(wc, f_name, &cont[1], cont[0]))
		return (0);
	return (1);
}

char	*ft_wildcard(char *wc)
{
	DIR				*dir_ptr;
	struct dirent	*directory;
	char			*file_list;
	char			*tmp;

	get_files_init(&dir_ptr, &directory);
	file_list = ft_strdup("");
	if (!directory || !file_list)
		return (NULL);
	while (directory)
	{
		if (ft_is_wildcard(directory->d_name, wc))
		{
			tmp = ft_strjoin(file_list, directory->d_name);
			freedom((void **)&file_list);
			file_list = ft_strjoin(tmp, " ");
			freedom((void **)&tmp);
		}
		directory = readdir(dir_ptr);
	}
	if (!file_list[0])
		return (freedom((void **)&file_list), closedir(dir_ptr), NULL);
	tmp = ft_strtrim(file_list, " \n\t\r\v");
	freedom((void **)&file_list);
	return (closedir(dir_ptr), tmp);
}
