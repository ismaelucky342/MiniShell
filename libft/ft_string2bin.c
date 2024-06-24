/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string2bin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:09:31 by ismherna          #+#    #+#             */
/*   Updated: 2024/06/12 01:38:57 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_string2bin(char *s, size_t i, size_t j)
{
	char	*ret;
	size_t	len;
	char	c;
	int		k;

	len = ft_strlen(s);
	ret = ft_calloc(len * 8 + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	while (i < len)
	{
		c = s[i];
		k = 7;
		while (k >= 0)
		{
			if ((c >> k) & 1)
				ret[j++] = '1';
			else
				ret[j++] = '0';
			k--;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}
