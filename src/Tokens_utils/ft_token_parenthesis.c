/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_parenthesis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:28:48 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 10:29:27 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_token_isparenthesis(t_token *token)
{
	return (ft_token_istype(token, CHAR_LEFT_PARENTHESIS
			| CHAR_RIGHT_PARENTHESIS));
}
