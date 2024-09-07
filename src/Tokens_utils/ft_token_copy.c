/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:29:55 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/07 17:10:51 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_token_copy(t_token *token, t_mem_context *ctx)
{
	t_token	*new;

	new = (t_token *)mmalloc(ctx, sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = token->type;
	new->position_in_line = token->position_in_line;
	new->length = token->length;
	new->value = ft_mstrdup(ctx, token->value);
	if (!new->value)
	{
		mfree(ctx, (void **)&new);
		return (NULL);
	}
	return (new);
}
