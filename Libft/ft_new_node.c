/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:00:33 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 15:54:12 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*initialize_node(t_mem_context *ctx, size_t size)
{
	return (mmalloc(ctx, size));
}

void	process_node(void *new, void (*f)(void *, int, va_list), int nb_arg,
		...)
{
	va_list	ap;

	va_start(ap, nb_arg);
	f(new, nb_arg, ap);
	va_end(ap);
}
