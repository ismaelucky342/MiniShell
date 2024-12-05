/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 20:11:15 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 10:07:09 by ismherna         ###   ########.fr       */
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
