/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:40:33 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 15:34:15 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_tokenizer_error(int opt, t_tokenizer *tz)
{
	if (opt == ERROR_UNKNOWN)
		ft_printf_fd(2, "minishell: unexpected \'end of line\' after \'%c\'\n",
			tz->previous_char);
	else if (opt == ERROR_UNSUPPORTED_FEATURE)
		ft_printf_fd(2, "minishell: warning this is not supported \'%c\'\n",
			tz->current_char);
	else if (opt == ERROR_UNSUPPORTED_FEATURE_AND)
		ft_printf_fd(2, "minishell: warning this is not supported \'&&\'\n");
	else if (opt == ERROR_UNSUPPORTED_FEATURE_OR)
		ft_printf_fd(2, "minishell: warning this is not supported \'||\'\n");
	else if (opt == ERROR_UNSUPPORTED_FEATURE_SUBSHELL)
		ft_printf_fd(2, "minishell: warning subshells not supported\n");
	else if (opt == ERROR_UNSUPPORTED_FEATURE_HEREDOC)
		ft_printf_fd(2, "minishell: warning heredocs not supported\n");
	else if (opt == ERROR_GET_NEXT_LINE)
		return (0);
	else
		ft_printf_fd(2, "minishell: invalid character \'%c\' (%#x)\n",
			tz->current_char, tz->current_char);
	return (ERROR);
}

int	unsupported_feature(t_tokenizer *tz, int *token_type, char curr, char next)
{
	*token_type = TYPE_ERROR;
	if (curr == '(')
		ft_tokenizer_error(ERROR_UNSUPPORTED_FEATURE_SUBSHELL, tz);
	else if (curr == ')')
		ft_tokenizer_error(ERROR_UNSUPPORTED_FEATURE_SUBSHELL, tz);
	else if (tz->line_length > 1 && curr == '<' && next == '<')
		ft_tokenizer_error(ERROR_UNSUPPORTED_FEATURE_HEREDOC, tz);
	else if (curr == '&')
		ft_tokenizer_error(ERROR_UNSUPPORTED_FEATURE, tz);
	else
	{
		*token_type = 0;
		return (0);
	}
	return (1);
}

int	ft_tokenizer_deftoken_double(t_tokenizer *tz,
			int *len, char curr, char next)
{
	if (tz->line_length > 1 && curr == '&' && next == '&')
	{
		*len = 2;
		return (TYPE_LOGICAL_AND);
	}
	if (tz->line_length > 1 && curr == '|' && next == '||')
	{
		*len = 2;
		return (TYPE_LOGICAL_OR);
	}
	if (tz->line_length > 1 && curr == '>' && next == '>')
	{
		*len = 2;
		return (TYPE_REDIR_OUTPUT);
	}
	return (0);
}

int	ft_isdefined_token_helper(t_tokenizer *tz, int *type_len,
		char current_next[2])
{
	if (unsupported_feature(tz, &type_len[0], current_next[0], current_next[1]))
		return (type_len[0]);
	else if (current_next[0] == '<')
	{
		type_len[1] = 1;
		type_len[0] = TYPE_REDIR_INPUT;
	}
	else if (current_next[0] == '>')
	{
		type_len[1] = 1;
		type_len[0] = TYPE_REDIR_OUTPUT;
	}
	else if (type_len[0] == TYPE_ERROR && current_next[0] == '|')
	{
		type_len[1] = 1;
		type_len[0] = TYPE_PIPE;
	}
	else if (current_next[0] == ';')
	{
		type_len[1] = 1;
		type_len[0] = TYPE_SEMICOLON;
	}
	else if (!type_len[0])
		return (TYPE_NONE);
	return (type_len[0]);
}

int	ft_isdefined_token(t_tokenizer *tz, int adv)
{
	int		type_len[2];
	char	current_next[2];

	type_len[1] = 0;
	if (!tz->current_line)
		return (TYPE_ERROR);
	current_next[0] = tz->current_char;
	if (tz->line_length > 1)
		current_next[1] = tz->current_line[tz->current_position + 1];
	else
		current_next[1] = 0;
	type_len[0] = ft_tokenizer_deftoken_double(tz, &type_len[1],
			current_next[0], current_next[1]);
	if (type_len[0] == TYPE_ERROR)
	{
		type_len[0] = ft_isdefined_token_helper(tz, type_len, current_next);
	}
	if (type_len[0] != TYPE_ERROR && adv == FOREACH_ADVANCE_ITERATOR)
		ft_tokenizer_advance(tz, type_len[1]);
	return (type_len[0]);
}
