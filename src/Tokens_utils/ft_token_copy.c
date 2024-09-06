/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:29:55 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 22:18:34 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_token_copy(t_token *token, t_mem_context *ctx)
{
	t_token	*new;

	new = mmalloc(ctx, sizeof(t_token));
	new->type = token->type;
	new->position_in_line = token->position_in_line;
	new->value = ft_strdup(token->value);
	new->length = token->length;
	return (new);
}
