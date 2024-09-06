/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:20:32 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 10:21:09 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_token_new(t_token_data*token_data,
						t_token_type_key type, char *value, int pos)
{
	t_token		*new;

	new = mmalloc(sizeof(t_token));
	new->type = type;
	new->position_in_line = pos;
	new->value = value;
	new->length = 0;
	if (value)
		new->length = ft_strlen(value);
	return (new);
}
