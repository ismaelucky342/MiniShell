/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:52:37 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/02 22:38:03 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**

	* @brief Encuentra el índice de una variable de entorno en un 
	array de entradas de entorno.
 *
 * Recorre un array de punteros a cadenas (`envp`) 
 * para buscar la clave (`key`).
 * Compara cada entrada con la clave y determina si hay una 
 * coincidencia exacta

	* (incluyendo el signo igual o el final de la cadena). 
	Si se encuentra la clave,
 * se devuelve su índice; de lo contrario, se retorna -1.
 *

	* @param envp Array de punteros a cadenas que representan las 
	variables de entorno.
 * @param key Clave de la variable de entorno a buscar.
 * @return int Índice de la variable de entorno si se encuentra,
	-1 si no existe.
 */
static int	ft_find_env_index(char **envp, char *key)
{
	int	i;
	int	j;

	i = 0;
	while (envp && envp[i])
	{
		j = 0;
		while (envp[i][j] && key[j] && (envp[i][j] == key[j]))
			++j;
		if (!key[j] && (envp[i][j] == '=' || !envp[i][j]))
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Elimina una variable de entorno del array de variables de entorno.
 *
 * Busca el índice de la variable de entorno especificada por `key` utilizando
 * `ft_find_env_index`. Si se encuentra la variable, se libera su memoria,
 * se decrementa el conteo de elementos y se desplazan las entradas restantes
 * para llenar el vacío. Si no se encuentra la variable, se retorna -1.
 *
 * @param boogeyman Puntero a la estructura principal que contiene el array de
 *                  variables de entorno y el conteo de elementos.
 * @param key Clave de la variable de entorno a eliminar.
 * @return int OK si la operación fue exitosa, -1 si la variable no existe.
 */
int	ft_remove_env(t_minishell *boogeyman, char *key)
{
	int	index;
	int	i;

	index = ft_find_env_index(boogeyman->envp, key);
	if (index == -1)
		return (-1);
	free(boogeyman->envp[index]);
	boogeyman->env_elems--;
	i = index;
	while (boogeyman->envp[i])
	{
		boogeyman->envp[i] = boogeyman->envp[i + 1];
		i++;
	}
	return (OK);
}
