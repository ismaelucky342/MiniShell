/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:23:18 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 22:19:34 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_token_del(t_token **token, t_mem_context *ctx)
{
	if (*token)
	{
		mfree(ctx, (void **)&(*token)->value);
		mfree(ctx, (void **)token);
	}
}
