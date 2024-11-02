/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:40:43 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/02 22:36:45 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Extrae el valor de una variable de entorno de una entrada dada.
 *

	* Compara una entrada de entorno (`env_entry`) con una clave (`key`) 
	para determinar
 * si corresponde a una variable de entorno. Si hay coincidencia,
	se devuelve un puntero

	* al valor asociado y se marca la existencia de la variable. 
	Si no hay coincidencia,
 * se devuelve NULL.
 *
 * @param env_entry Entrada de entorno que se está evaluando.
 * @param key Clave de la variable de entorno a buscar.

	* @param exists Puntero a un entero que se establece en 1 
	si la variable existe,
 *               o no se modifica si la variable no se encuentra.
 * @return char* Puntero al valor de la variable de entorno si existe,
	NULL si no.
 */
static char	*extract_value(char *env_entry, char *key, int *exists)
{
	int	key_len;

	key_len = ft_strlen(key);
	if (!ft_strncmp(env_entry, key, key_len) && env_entry[key_len] == '=')
	{
		if (exists)
			*exists = 1;
		return (env_entry + key_len + 1);
	}
	return (NULL);
}

/**

	* @brief Obtiene el valor de una variable de entorno de un array de entradas 
	de entorno.
 *

	* Recorre un array de punteros a cadenas (`envp`) en busca de una clave 
	específica
 * (`key`). Llama a `extract_value` para determinar si una entrada en `envp`
 * corresponde a la clave. Si se encuentra,
	se devuelve el valor asociado; si no,
 * se indica que la variable no existe.
 *

	* @param envp Array de punteros a cadenas que representan las variables 
	de entorno.
 * @param key Clave de la variable de entorno cuyo valor se busca.

	* @param exists Puntero a un entero que se establece en 1 si la variable 
	existe,
 *               o en 0 si no se encuentra.
 * @return char* Valor de la variable de entorno si se encuentra, cadena vacía
 *                si no existe.
 */
char	*get_value_from_env(char **envp, char *key, int *exists)
{
	char	*value;
	int		i;

	i = 0;
	while (envp && envp[i])
	{
		value = extract_value(envp[i], key, exists);
		if (value)
			return (value);
		i++;
	}
	if (exists)
		*exists = 0;
	return ("");
}
