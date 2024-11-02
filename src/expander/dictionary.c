/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:50:33 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/02 22:40:14 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Extrae un substring desde una posición específica en una cadena.
 *
 * La función busca en la cadena `str` desde el índice `needle_tip` y extrae un 
 * substring que termina en el primer espacio, comillas, o uno de los 
 * caracteres especiales (`|`, `;`, `&`, `$`). También maneja casos 
 * especiales para el signo de dólar (`$`) y el signo de interrogación (`?`).
 *
 * @param str Cadena de entrada desde la cual se extraerá el substring.
 * @param needle_tip Posición de inicio para la extracción.
 * @return char* Un nuevo substring extraído. Si se encuentra un caso especial 
 *               o no hay caracteres válidos, se devuelve una cadena vacía o 
 *               un puntero a `"$"` o `"?"`.
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
