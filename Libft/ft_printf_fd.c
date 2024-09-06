/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:03:40 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 14:19:22 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cont(char *buf, const char **format, va_list ap, int i)
{
	int	dir[11];
	int	j;

	while (**format && i < PF_BUFF_SIZE - 65)
	{
		if (**format != '%')
			buf[i++] = *(*format)++;
		else
		{
			(*format)++;
			while (j > 0)
				dir[--j] = -1;
			ft_initdir(dir, format, ap);
			ft_specifier(dir, format, i, ap);
			if (dir[PF_SPEC] < 1 || dir[PF_SPEC] == 8)
				i += to_c(&buf[i], dir, ap);
			else if (dir[PF_SPEC] == 1)
				i += to_s(&buf[i], dir, ap);
			else if (dir[PF_SPEC] > 1 && dir[PF_SPEC] < 9)
				i += to_nbr(&buf[i], dir, ap);
		}
		if (*(*format - 1) == '\n')
			return (i);
	}
	return (i);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	char	buf[PF_BUFF_SIZE];
	va_list	ap;
	int		printed;
	int		last;

	if (format == NULL)
		return (-1);
	printed = 0;
	va_start(ap, format);
	while (*format)
	{
		last = ft_cont(buf, &format, ap, 0);
		write(fd, buf, last);
		printed += last;
	}
	va_end(ap);
	return (printed);
}
