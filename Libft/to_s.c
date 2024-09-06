/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:57:52 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 15:18:58 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	to_s(char *buf, int *dir, va_list ap)
{
	char	*str;
	char	*s;
	char	fill;
	int		len;
	int		i;

	s = va_arg(ap, char *);
	if (s == NULL)
		s = NULLSTR;
	len = ft_strnlen(s, dir[PF_PREC]);
	fill = ' ';
	if (dir[PF_ZERO] == 1)
		fill = '0';
	str = buf;
	i = -1;
	if (dir[PF_LEFT] != 1)
	{
		while (len < dir[PF_WIDTH]--)
			*str++ = fill;
	}
	while (++i < len)
		*str++ = *s++;
	while (len < dir[PF_WIDTH]--)
		*str++ = ' ';
	return (str - buf);
}
