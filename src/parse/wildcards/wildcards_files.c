/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:52:38 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 17:30:46 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	get_files(DIR **dir_ptr, struct dirent **directory)
{
	*dir_ptr = opendir(".");
	*directory = readdir(*dir_ptr);
}

int	regex_iterator(char *regex, char *f_name, int *j, int i)
{
	while (regex[*j] == '*')
		++*j;
	if (f_name[i] || (regex[*j]))
		return (OK);
	return (KO);
}
