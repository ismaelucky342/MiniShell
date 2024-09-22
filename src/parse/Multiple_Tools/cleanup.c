/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:11:08 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/20 17:29:45 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_array_free(char **array)
{
	int	pos;

	pos = 0;
	if (!array)
		return ;
	while (array[pos])
		free(array[pos++]);
	free(array);
}

void	free_cmd_token(void *tok)
{
	t_token *tofree;

	tofree = tok;
	if (tofree)
	{
		if (tofree->str)
			free(tofree->str);
		free(tofree);
	}
}