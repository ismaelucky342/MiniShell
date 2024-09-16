/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:59:01 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/12 16:22:28 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_hashtable(t_hashtable *hashtable)
{
	t_element	*current;
	t_element	*next;
	int			i;

	i = 0;
	if (!hashtable || !hashtable->element_array)
		return ;
	while (i < hashtable->length)
	{
		current = hashtable->element_array[i];
		while (current)
		{
			next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			current = next;
		}
		i++;
	}
	free(hashtable->element_array);
	free(hashtable);
}

