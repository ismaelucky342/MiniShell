/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:29:40 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 15:30:07 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Extracts a substring from the input string starting at 
		the given position.
 *
 * This function takes a string and a starting position (needle_tip)
		and returns a 
 * substring that ends at the first occurrence of a special character
		or whitespace.
 * The special characters considered are: space (' '), double quote ('"'),
		single quote ('\''),
 * pipe ('|'), semicolon (';'), ampersand ('&'), and dollar sign ('$').
 *
 * @param str The input string from which the substring is extracted.
 * @param needle_tip The starting position in the input string.
 * @return A newly allocated string containing the extracted substring.
 *         If the character at needle_tip is '$', returns "$".
 *         If the character at needle_tip is '?', returns "?".
 *         If the character at needle_tip is a whitespace, null terminator,
	or double quote, returns an empty string.
 */
char	*dictionary(char *str, int needle_tip)
{
	size_t	len;

	if (str[needle_tip] == '$')
		return (ft_strdup("$"));
	if (str[needle_tip] == '?')
		return (ft_strdup("?"));
	if (ft_isspace(str[needle_tip]) || !str[needle_tip]
		|| str[needle_tip] == '"')
		return (ft_strdup(""));
	len = ft_strchr(&str[needle_tip], ' ') - &str[needle_tip];
	if (len > (size_t)(ft_strchr(&str[needle_tip], '"') - &str[needle_tip]))
		len = ft_strchr(&str[needle_tip], '"') - &str[needle_tip];
	if (len > (size_t)(ft_strchr(&str[needle_tip], '\'') - &str[needle_tip]))
		len = ft_strchr(&str[needle_tip], '\'') - &str[needle_tip];
	if (len > (size_t)(ft_strchr(&str[needle_tip], '|') - &str[needle_tip]))
		len = ft_strchr(&str[needle_tip], '|') - &str[needle_tip];
	if (len > (size_t)(ft_strchr(&str[needle_tip], ';') - &str[needle_tip]))
		len = ft_strchr(&str[needle_tip], ';') - &str[needle_tip];
	if (len > (size_t)(ft_strchr(&str[needle_tip], '&') - &str[needle_tip]))
		len = ft_strchr(&str[needle_tip], '&') - &str[needle_tip];
	if (len > (size_t)(ft_strchr(&str[needle_tip], '$') - &str[needle_tip]))
		len = ft_strchr(&str[needle_tip], '$') - &str[needle_tip];
	if (len == 0)
		len = SIZE_T_MAX;
	return (ft_substr(str, needle_tip, len));
}
