/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:49:31 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/07 12:52:07 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_error(char *title, int code, char *line)
{
	char	*str;
	char	*cmd;

	cmd = ft_strtrim(line, " ");
	str = ft_strjoin(title, cmd);
	if (!str)
		exit(1);
	ft_putendl_fd(str, 2);
	free(str);
	free(cmd);
	exit(code);
}
