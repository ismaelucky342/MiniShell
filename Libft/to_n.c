/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_n.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:57:52 by ismherna          #+#    #+#             */
/*   Updated: 2024/02/15 10:56:39 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	to_n(int printed, int *dir, va_list ap)
{
	int	*ptr;

	if (dir[PF_LONG] >= 0)
	{
		if (dir[PF_LONG] == 0)
			ptr = (int *)va_arg(ap, long *);
		else
			ptr = (int *)va_arg(ap, long long *);
	}
	else if (dir[PF_SHORT] >= 0)
	{
		if (dir[PF_SHORT] == 0)
			ptr = (int *)va_arg(ap, short int *);
		else
			ptr = (int *)va_arg(ap, signed char *);
	}
	else
		ptr = va_arg(ap, int *);
	*ptr = printed;
}
