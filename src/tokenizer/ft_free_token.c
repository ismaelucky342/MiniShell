/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:59:11 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:58:30 by dgomez-l         ###   ########.fr       */
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
	t_token		*tofree;

	tofree = tok;
	if (tofree)
	{
		if (tofree->str)
			free(tofree->str);
		free(tofree);
	}
}
