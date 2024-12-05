/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:15:01 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/12/05 13:06:31 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "../../includes/minishell.h"

/**
 * @brief Processes wildcard characters in a file name based on the provided wc.
 *
 * This function increments the indices in `cont` based on the characters in the file name
 * and the regular expression, checking for wildcard patterns. It also updates the indices 
 * when the current character is not the null terminator.
 *
 * @param cont An array holding two integers: [current index in file name, current index in wc].
 * @param f_name The file name to be processed.
 * @param wc The regular expression to be checked against the file name.
 */
void	wildcard_process(int *cont, char *f_name, char*wc)
{
	if (f_name[cont[0]] != '\0')
		++(cont[0]);
	if (f_name[cont[0]] != '\0')
		++(cont[1]);
	if (!wc[cont[1]] && f_name[cont[0]])
	{
		while (wc[cont[1]] != '*')
			--cont[1];
	}
}

/**
 * @brief Initializes the directory pointer and reads the first directory entry.
 *
 * This function opens the current directory and reads the first entry into the 
 * provided `directory` pointer.
 *
 * @param dir_ptr A pointer to a directory pointer, which is initialized with the result of opendir.
 * @param directory A pointer to the directory entry that is read.
 */
void	get_files_init(DIR **dir_ptr, struct dirent **directory)
{
	*dir_ptr = opendir(".");
	*directory = readdir(*dir_ptr);
}

/**
 * @brief Iterates over the wc and file name to check for matching characters.
 *
 * This function skips over '*' characters in the wc, then compares the file name 
 * character at the current index with the wc character. It returns 1 if the end of 
 * both strings is reached, and 0 otherwise.
 *
 * @param wc The regular expression to be checked.
 * @param f_name The file name to be compared with the wc.
 * @param j A pointer to the current index in the wc.
 * @param i The current index in the file name.
 * @return 1 if the end of both the wc and file name are reached, otherwise 0.
 */
int	wc_iterator(char *wc, char *f_name, int *j, int i)
{
	while (wc[*j] == '*')
		++*j;
	if (f_name[i] || (wc[*j]))
		return (0);
	return (1);
}

