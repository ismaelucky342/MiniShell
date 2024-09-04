/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hashtable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:03:30 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/04 13:03:30 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_hashtable(t_hashtable *hashtable, char *delimeter)
{
	int	index;

	index = 0;
	while (index < hashtable->length)
	{
		if (hashtable->element_array[index])
		{
			ft_putstr_fd(hashtable->element_array[index]->key, 1);
			ft_putstr_fd(delimeter, 1);
			ft_putstr_fd(hashtable->element_array[index]->value, 1);
			ft_putstr_fd("\n", 1);
		}
		index++;
	}
}
