/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isreserved.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:46:44 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 13:10:18 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_isreserved(char c)
{
	if (c != '|' && c != ';' && c != '<' && c != '>' && c != '&')
		return (0);
	return (1);
}