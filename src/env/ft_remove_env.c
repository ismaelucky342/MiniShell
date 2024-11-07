/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:52:37 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/03 12:54:19 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**

* @brief Finds the index of an environment variable in an array of
environment entries.
*
* Iterates through an array of string pointers (`envp`)
* to find the key (`key`).
* Compares each entry to the key and determines if there is an
* exact match (including the equal sign or the end of the string).
If the key is found, its index is
* returned; otherwise, -1 is returned.
*

* @param envp Array of string pointers representing the
environment variables.
* @param key Key of the environment variable to find.
* @return int Index of the environment variable if found,
-1 if not.
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
