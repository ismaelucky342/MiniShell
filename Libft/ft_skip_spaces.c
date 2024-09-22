/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:21:05 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:25:19 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	skip_spaces(char *str, int *i, int *start, int mode)
{
	while (ft_isspace(str[*i]) && str[*i])
		++(*i);
	if (mode)
		*start = *i;
}
