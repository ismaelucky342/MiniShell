/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:00:18 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:30:54 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Frees a dynamically allocated array of strings.
 *
 * This function iterates through the array and frees each string it contains,
 * then frees the array itself.
 *
 * @param array A pointer to the array of strings to be freed.
 */
void	ft_free_array(char **array)
{
	int	pos;

	pos = 0;
	if (!array)
		return ;
	while (array[pos])
		free(array[pos++]);
	free(array);
}
