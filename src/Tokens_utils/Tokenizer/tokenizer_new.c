/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:15:13 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 22:33:04 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_tokenizer	*ft_tokenizer_new(int sloc, t_mem_context *ctx)
{
	t_tokenizer	*tz;

	tz = mmalloc(ctx, sizeof(t_tokenizer));
	if (ft_tokenizer_refill_line(tz, sloc, ctx) == ERROR)
	{
		ft_tokenizer_delete(&tz, ctx);
		return (NULL);
	}
	return (tz);
}
