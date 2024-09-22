/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_reserved_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:12:14 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/22 18:24:26 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_is_reserved_char(char c)
{
	if (c != '|' && c != ';' && c != '<' && c != '>' && c != '&')
		return (0);
	return (1);
}
