/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:57:52 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 14:27:28 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*mmalloc(t_mem_context *ctx, unsigned int size)
{
	void	*new;
	t_list	*list;

	new = malloc(size + 1);
	if (!new)
	{
		free_all_malloc(ctx);
		ft_printf_fd(2, "allocation error");
		exit(1);
	}
	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
	{
		free(new);
		free_all_malloc(ctx);
		ft_printf_fd(2, "allocation error");
		exit(1);
	}
	ft_bzero(new, size);
	list->data = new;
	list->next = ctx->allocated_list;
	ctx->allocated_list = list;
	return (new);
}

int	free_all_malloc(t_mem_context *ctx)
{
	t_list	*prev;

	while (ctx->allocated_list)
	{
		free(ctx->allocated_list->data);
		prev = ctx->allocated_list;
		ctx->allocated_list = ctx->allocated_list->next;
		free(prev);
	}
	return (0);
}

int	mfree(t_mem_context *ctx, void **to_free)
{
	t_list	**indir;
	t_list	*f;

	if (!*to_free)
		return (0);
	indir = &ctx->allocated_list;
	while (*indir && (*indir)->data != *to_free)
		indir = &((*indir)->next);
	f = *indir;
	if (f)
	{
		*indir = (*indir)->next;
		free(f->data);
		free(f);
		*to_free = NULL;
	}
	return (0);
}
