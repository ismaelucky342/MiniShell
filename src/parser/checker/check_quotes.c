/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:53:50 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/08/31 16:53:52 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_quotes(char *command)
{
	char	quotes;
	int		parentesis;

	parentesis = 0;
	while (*command && parentesis >= 0)
	{
		if (*command == '(')
			parentesis++;
		if (*command == ')')
			parentesis--;
		if (*command == '"' || *command == '\'')
		{
			quotes = *command;
			command++;
			while (*command && *command != quotes)
				command++;
			if (!*command)
				return (-1 - !isatty(STDIN_FILENO));
		}
		if (parentesis < 0)
			return (-2);
		command++;
	}
	return ((-1 - !isatty(STDIN_FILENO)) * (parentesis > 0));
}
