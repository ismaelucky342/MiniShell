/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:57:52 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 14:29:20 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_buffer_with_char(char *buf, int width, char fill)
{
	while (0 < width--)
		*buf++ = fill;
}

static int	get_spec_char(int *dir, va_list ap)
{
	if (dir[PF_SPEC] == -1)
		return ('\0');
	else if (dir[PF_SPEC] == 8)
		return ('%');
	else
		return (va_arg(ap, int));
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
	{
		fill_buffer_with_char(str, dir[PF_WIDTH], fill);
		str += dir[PF_WIDTH];
	}
	spec_char = get_spec_char(dir, ap);
	*str++ = spec_char;
	fill_buffer_with_char(str, dir[PF_WIDTH], ' ');
	if (spec_char == '\0')
		return (str - buf - 1);
	else
		return (str - buf);
}
