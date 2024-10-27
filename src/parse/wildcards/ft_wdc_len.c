/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wdc_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:49:57 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 17:30:42 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	strlen_and_free(char **tmp, char **tmp2, char **file)
{
	int	i;

	*tmp = *tmp2;
	if (*file)
	{
		i = (1 + ft_strlen(*file));
		free(*file);
		return (i);
	}
	else
		return (-1);
}
