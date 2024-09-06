/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_nbr_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:57:52 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 14:52:42 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_itoa_b(char *addr, unsigned long long nbr, int *dir)
{
	char	*xbase;
	int		i;
	char	n[70];
	int		base;

	i = 0;
	if (dir[PF_SPEC] == 6 || dir[PF_SPEC] == 7 || dir[PF_SPEC] == 2)
		base = 16;
	else
		base = 10;
	if (dir[PF_SPEC] == 7)
		xbase = "0123456789ABCDEF";
	else
		xbase = "0123456789abcdef";
	if (nbr == 0 && dir[PF_PREC] != 0)
		n[i++] = '0';
	while (nbr != 0)
	{
		n[i++] = xbase[nbr % base];
		nbr = nbr / base;
	}
	n[i] = '\0';
	while (addr && --i >= 0)
		*addr++ = n[i];
	*addr = '\0';
}

char	*fill_width(char *str, int *dir, char fill_char)
{
	while (0 < dir[PF_WIDTH]--)
		*str++ = fill_char;
	return (str);
}

char	*ft_number_str(char *n, char *str, char sign, int *dir)
{
	int	len;

	len = ft_strnlen(n, -1);
	if (dir[PF_LEFT] != 1 && dir[PF_ZERO] != 1)
		str = fill_width(str, dir, ' ');
	if (sign != 0)
		*str++ = sign;
	if (dir[PF_SPEC] == 2 || (dir[PF_S] == 1
			&& dir[PF_SPEC] >= 6 && dir[PF_SPEC] <= 7))
	{
		*str++ = '0';
		if (dir[PF_SPEC] == 7)
			*str++ = 'X';
		else
			*str++ = 'x';
	}
	if (dir[PF_LEFT] != 1)
		str = fill_width(str, dir, '0');
	while (dir[PF_PREC]-- > len)
		*str++ = '0';
	while (n && *n && len-- > 0)
		*str++ = *n++;
	if (dir[PF_LEFT] == 1)
		str = fill_width(str, dir, ' ');
	return (str);
}

long long	get_nbr(int *dir, va_list ap)
{
	if (dir[PF_SPEC] == 2)
		return (((unsigned long long)va_arg(ap, void *)));
	else if (dir[PF_SPEC] == 5 || dir[PF_SPEC] == 6 || dir[PF_SPEC] == 7)
	{
		if (dir[PF_LONG] == 0)
			return ((unsigned long long)va_arg(ap, unsigned long));
		else if (dir[PF_LONG] == 1)
			return ((va_arg(ap, unsigned long long)));
		else if (dir[PF_SHORT] == 0)
			return ((unsigned short int)va_arg(ap, unsigned int));
		else if (dir[PF_SHORT] == 1)
			return ((unsigned char)va_arg(ap, unsigned int));
		else
			return ((unsigned long long)va_arg(ap, unsigned int));
	}
	if (dir[PF_LONG] == 0)
		return ((long long)va_arg(ap, long));
	else if (dir[PF_LONG] == 1)
		return ((long long)va_arg(ap, long long));
	else if (dir[PF_SHORT] == 0)
		return ((short int)va_arg(ap, int));
	else if (dir[PF_SHORT] == 1)
		return ((signed char)va_arg(ap, int));
	else
		return ((long long)va_arg(ap, int));
}
