/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:59:30 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 16:44:48 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Given a logically expandable char *str,
 * returns the corresponding left expanded node.
 *
 * @param str The input string to process.
 * @return The left token extracted from the input string.
 */

char	*ft_get_left_token(char *str)
{
	int		i;
	int		last;
	char	*tmp;
	char	*res;

	i = 0;
	last = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			state_quote_delimiter(str, &i, str[i]);
			if (str[i] == '\'' || str[i] == '\"')
				++i;
		}
		else if (str[i] == '(')
			ft_brackets(str, &i);
		else
			++i;
		if ((str[i] == '&' && str[i + 1] == '&') || (str[i] == '|' && str[i
					+ 1] == '|') || str[i] == ';')
			last = i;
	}
	tmp = ft_substr(str, 0, last);
	return (res = ft_strtrim(tmp, " \n\t\v\r"), free(tmp), res);
}

/**
 * Given a logically expandable char *str,
 * returns the corresponding right expanded node.
 *
 * @param str The input string to process.
 * @return The right token extracted from the input string.
 */
char	*ft_get_right_token(char *str)
{
	int		i;
	int		last;
	char	*tmp;
	char	*res;

	i = 0;
	last = 0;
	while (str[i])
		is_quote(str, &i, &last);
	if ((str[last] == '&' && str[last + 1] == '&') || (str[last] == '|'
			&& str[last + 1] == '|'))
		++last;
	tmp = ft_substr(str, last + 1, SIZE_T_MAX);
	return (res = ft_strtrim(tmp, " \n\t\v\r"), free(tmp), res);
}
