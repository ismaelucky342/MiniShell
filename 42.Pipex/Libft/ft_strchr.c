/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:20:13 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/01/09 11:20:15 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		count_str;
	char	*str;

	str = (char *)s;
	count_str = 0;
	while (str[count_str] != 0)
	{
		if (str[count_str] == (unsigned char)c)
			return (str + count_str);
		count_str ++;
	}
	if (str[count_str] == (unsigned char)c)
		return (str + count_str);
	return (0);
}
