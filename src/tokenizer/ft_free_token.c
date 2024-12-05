/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:59:11 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 12:59:21 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Frees a token object.
 *
 * This function frees the memory allocated for the string and the token 
 * structure itself.
 *
 * @param tok A pointer to the token to be freed.
 */
void	free_cmd_tok(void *tok)
{
	t_token	*tofree;

	tofree = tok;
	if (tofree)
	{
		if (tofree->str)
			free(tofree->str);
		free(tofree);
	}
}