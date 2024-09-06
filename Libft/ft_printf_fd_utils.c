/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:03:40 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 15:57:11 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_specifier(int *dir, const char **format, int i, va_list ap)
{
	int	c;

	while (**format == 'h' || **format == 'l')
	{
		if (**format == 'l')
			dir[PF_LONG]++;
		if (**format == 'h')
			dir[PF_SHORT]++;
		(*format)++;
	}
	c = -1;
	while (C_SPEC[++c])
	{
		if (C_SPEC[c] == **format)
			break ;
	}
	if (C_SPEC[c] == '\0')
		c = -1;
	dir[PF_SPEC] = c;
	if (dir[PF_SPEC] >= 0)
		(*format)++;
	if (dir[PF_SPEC] == 9)
		to_n(i, dir, ap);
}

void	handle_format_flags(int *dir, const char **f)
{
	if (**f == '0')
		dir[PF_ZERO] = 1;
	if (**f == '-')
		dir[PF_LEFT] = 1;
	if (**f == '+')
		dir[PF_PLUS] = 1;
	if (**f == ' ')
		dir[PF_SPACE] = 1;
	if (**f == '#')
		dir[PF_S] = 1;
}

void	process_width_precision(int *dir, const char **f, va_list ap)
{
	if (**f == '.')
	{
		(*f)++;
		dir[PF_PREC] = 0;
		if (**f >= '0' && **f <= '9')
			dir[PF_PREC] = skip_atoi(f);
		else if (**f == '*')
		{
			(*f)++;
			dir[PF_PREC] = va_arg(ap, int);
			if (dir[PF_PREC] < 0)
				dir[PF_PREC] = -dir[PF_PREC];
		}
	}
	else if (**f >= '1' && **f <= '9')
		dir[PF_WIDTH] = skip_atoi(f);
	else if (**f == '*')
	{
		(*f)++;
		dir[PF_WIDTH] = va_arg(ap, int);
		if (dir[PF_WIDTH] < 0)
			dir[PF_LEFT] = 1;
		if (dir[PF_WIDTH] < 0)
			dir[PF_WIDTH] = -dir[PF_WIDTH];
	}
}

void	ft_initdir(int *dir, const char **f, va_list ap)
{
	while (**f == '+' || **f == '*' || **f == '-' || **f == '.'
		|| **f == '#' || **f == ' ' || **f == '\''
		|| (**f >= '0' && **f <= '9'))
	{
		handle_format_flags(dir, f);
		process_width_precision(dir, f, ap);
		if (**f != '+' && **f != '*' && **f != '-' && **f != '.'
			&& **f != '#' && **f != ' ' && **f != '\''
			&& !(**f >= '0' && **f <= '9'))
		{
			(*f)++;
		}
	}
}
