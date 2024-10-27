/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:31:39 by ismherna          #+#    #+#             */
/*   Updated: 2024/10/27 17:28:44 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_exit;

int	ft_check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			skip_to_delimiter(str, &i, str[i]);
			if (!str[i])
			{
				ft_quote_error();
				return (KO);
			}
			else
				++i;
		}
		else
			++i;
	}
	return (OK);
}

int	ft_check_brackets(char *str)
{
	int	opening;
	int	closing;
	int	i;

	opening = 0;
	closing = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			skip_to_delimiter(str, &i, str[i]);
		else if (str[i] == '(')
			++opening;
		else if (str[i] == ')')
			++closing;
		if (str[i])
			++i;
	}
	if (opening != closing)
	{
		ft_bracket_error();
		return (KO);
	}
	return (OK);
}

int	ft_create_heredocs(char **str)
{
	int		i;
	char	*f_name;

	i = 0;
	f_name = NULL;
	while ((*str)[i] && g_exit)
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
			skip_to_delimiter(*str, &i, (*str)[i]);
		if (!ft_strncmp("<<", &(*str)[i], 2))
			if (ft_heredoc(str, &i, &f_name))
				return (KO);
		waitpid(-1, NULL, 0);
		if (f_name)
		{
			if (!g_exit)
				unlink(f_name);
			free(f_name);
			f_name = NULL;
		}
		if ((*str)[i])
			++i;
	}
	return (OK);
}

int	ft_check_fredirs(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i] && !check)
	{
		if (str[i] == '\'' || str[i] == '"')
			skip_to_delimiter(str, &i, str[i]);
		else if (!ft_strncmp("<<", &str[i], 2) || !ft_strncmp("<", &str[i], 1)
			|| !ft_strncmp(">>", &str[i], 2) || !ft_strncmp(">", &str[i], 1))
		{
			check = ft_check_file(str, &i);
		}
		else
			++i;
		if (check)
			return (check);
	}
	return (OK);
}
