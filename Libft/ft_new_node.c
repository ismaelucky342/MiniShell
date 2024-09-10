/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:00:33 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/10 12:14:49 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*initialize_node(size_t size)
{
	return (malloc(size));
}

void	process_node(void *new, void (*f)(void *, int, va_list), int nb_arg,
		...)
{
	va_list	ap;

	va_start(ap, nb_arg);
	f(new, nb_arg, ap);
	va_end(ap);
}
