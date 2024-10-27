/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:22:03 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/09 11:22:05 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		count_str;
	char	*str;
	char	*res;
	int		control;

	count_str = 0;
	control = 0;
	str = (char *)s;
	while (str[count_str] != 0)
	{
		if (str[count_str] == (unsigned char)c)
		{
			res = str + count_str;
			control = 1;
		}
		count_str ++;
	}
	if (str[count_str] == (unsigned char)c)
		return (str + count_str);
	if (control == 1)
		return (res);
	return (0);
}
