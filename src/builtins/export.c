/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:53:44 by ismherna          #+#    #+#             */
/*   Updated: 2024/12/05 12:30:17 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Checks if the given key is a valid environment variable key.
 *
 * This function verifies if the provided key is a valid identifier for an
 * environment variable. A valid key must contain at least one alphabetic
 * character and can only contain alphanumeric characters. The key cannot
 * contain spaces or equal signs.
 *
 * @param passkey The key to be validated.
 * @return 1 if the key is valid, 0 otherwise.
 */

static int	ft_is_valid_key(char	*passkey)
{
	int		i;
	char	has_alpha;

	i = -1;
	has_alpha = 0;
	while (passkey[++i] && passkey[i] != '=' && !ft_isspace(passkey[i]))
	{
		if (ft_isalpha(passkey[i]))
			has_alpha = 1;
		else if (!ft_isalnum(passkey[i]))
		{
			has_alpha = 0;
			break ;
		}
	}
	if (i != 0 && has_alpha)
		return (1);
	ft_putstr_fd("MiniShell: export: not a valid id: '", STDERR_FILENO);
	ft_putstr_fd(passkey, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (0);
}

/**
 * @brief Prints the current environment variables in a specific format.
 *
 * This function prints all the environment variables stored in the provided
 * array in the format "declare -x KEY="VALUE"", where VALUE is enclosed in
 * double quotes if it contains an equal sign.
 *
 * @param envp The array of environment variables.
 * @return Always returns 0.
 */

static int	ft_print_env(char **envp)
{
	int		i;
	int		j;
	char	flag;

	i = -1;
	while (envp[++i])
	{
		j = -1;
		flag = 0;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (envp[i][++j])
		{
			ft_putchar_fd(envp[i][j], STDOUT_FILENO);
			if (envp[i][j] == '=')
			{
				flag = 1;
				ft_putchar_fd('"', STDOUT_FILENO);
			}
		}
		if (flag)
			ft_putchar_fd('"', STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (0);
}
/**
 * @brief Handles the export builtin command in the minishell.
 *
 * This function processes the export command, which sets environment variables.
 * If no arguments are provided, it prints the current environment variables.
 * Otherwise, it validates each provided key and adds it to the environment if
 * valid.
 *
 * @param node The command node containing the arguments.
 * @param boogeyman The minishell structure containing the environment.
 * @return 0 if all keys are valid, 1 if any key is invalid.
 */

int	ft_export_builtin(t_tree_node *node, t_minishell *boogeyman)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	node->is_builtin = 1;
	if (!node->args[1])
		return (ft_print_env(boogeyman->envp));
	while (node->args[++i])
	{
		if (ft_is_valid_key(node->args[i]))
			ft_add_to_env(boogeyman, node->args[i]);
		else
			ret = 1;
	}
	return (ret);
}
