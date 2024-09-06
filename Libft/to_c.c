/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:57:52 by ismherna          #+#    #+#             */
/*   Updated: 2024/02/15 10:56:39 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	support(int *dir, char *str, char *buf)
{
	if (dir[PF_SPEC] == -1)
		return (str - buf - 1);
	else
		return (str - buf);
}

int	to_c(char *buf, int *dir, va_list ap)
{
	char	*str;
	char	fill;
	int		spec_char;

	str = buf;
	fill = ' ';
	dir[PF_WIDTH]--;
	if (dir[PF_PREC] == -1 && dir[PF_ZERO] == 1)
		fill = '0';
	if (dir[PF_LEFT] != 1)
		while (0 < dir[PF_WIDTH]--)
			*str++ = fill;
	if (dir[PF_SPEC] == -1)
		spec_char = '\0';
	else
	{
		if (dir[PF_SPEC] == 8)
			spec_char = '%';
		else
			spec_char = va_arg(ap, int);
	}
	*str++ = spec_char;
	while (0 < dir[PF_WIDTH]--)
		*str++ = ' ';
	return (support(dir, str, buf));
}
