/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:15:13 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 11:43:15 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_tokenizer	*ft_tokenizer_new(int sloc, t_global_state *state)
{
	t_tokenizer		*tz;

	tz = mmalloc(sizeof(t_tokenizer));

	if (ft_tokenizer_refill_line(tz, sloc, state) == ERROR)
	{
		ft_tokenizer_delete(&tz);
		return (NULL);
	}
	return (tz);
}
