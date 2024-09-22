/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:52:13 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/20 17:29:45 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void increment_index_if_char_present(char token, int *index)
{
    if (token != '\0')
        ++(*index);
}

void	handle_wildcard(int *cont, char *file_name, char*regex)
{
    increment_index_if_char_present(file_name[cont[0]], &cont[1]);
    increment_index_if_char_present(file_name[cont[0]], &cont[0]);

    if (!regex[cont[1]] && file_name[cont[0]])
    {
        while (regex[cont[1]] != '*' && cont[1] > 0)
            --cont[1];
    }
}

