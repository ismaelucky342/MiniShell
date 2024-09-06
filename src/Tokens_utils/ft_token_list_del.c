/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_list_del.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:23:35 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 22:20:30 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_token_list_del(t_token **token, t_mem_context *ctx)
{
	t_token	*tmp;
	t_token	*tmpnext;

	tmp = *token;
	while (tmp)
	{
		tmpnext = tmp->next;
		ft_token_del(&tmp, ctx);
		tmp = tmpnext;
	}
}
