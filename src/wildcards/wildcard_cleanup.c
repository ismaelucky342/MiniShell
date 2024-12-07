/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:02:43 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 17:01:18 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Calculates the length of a string and frees a
		previously allocated memory.
 *
 * This function sets `*tmp` to the value of `*tmp2`,
	then checks if `*file` is non-null.
 * If it is, the function calculates its length, frees `*file`,
	and returns the length.
 * If `*file` is null, the function returns -1.
 *
 * @param tmp A pointer to the current string.
 * @param tmp2 A pointer to a new string to set `*tmp` to.
 * @param file A pointer to the string to be freed and whose
		length is calculated.
 * @return The length of the string, or -1 if `*file` is null.
 */
int	strlen_and_free(char **tmp, char **tmp2, char **file)
{
	int		i;

	*tmp = *tmp2;
	if (*file)
	{
		i = (1 + ft_strlen(*file));
		free(*file);
		return (i);
	}
	else
		return (-1);
}
