/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:04:35 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:04:37 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnlen(char *str, int n)
{
	int	i;

	i = 0;
	if (n != -1)
		while (str && str[i] && i < n)
			i++;
	else
		while (str && str[i])
			i++;
	return (i);
}
