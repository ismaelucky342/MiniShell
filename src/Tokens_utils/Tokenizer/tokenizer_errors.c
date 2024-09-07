/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:40:33 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/07 15:45:40 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_error_unknown(t_tokenizer *tz, int code)
{
	char	*line;

	line = ft_strjoin("unexpected 'end of line' after '",
			ft_strchr(&tz->previous_char, '\0'));
	if (line)
	{
		ft_print_error("minishell: ", code, line);
		free(line);
	}
}

void	handle_error_unsupported_feature(t_tokenizer *tz, int code)
{
	char	*line;

	line = ft_strjoin("warning this is not supported '",
			ft_strchr(&tz->current_char, '\0'));
	if (line)
	{
		ft_print_error("minishell: ", code, line);
		free(line);
	}
}

void	handle_specific_errors(int opt, int code)
{
	if (opt == ERROR_UNSUPPORTED_FEATURE_AND)
		ft_print_error("minishell: ", code,
			"warning this is not supported '&&'\n");
	else if (opt == ERROR_UNSUPPORTED_FEATURE_OR)
		ft_print_error("minishell: ", code,
			"warning this is not supported '||'\n");
	else if (opt == ERROR_UNSUPPORTED_FEATURE_SUBSHELL)
		ft_print_error("minishell: ", code,
			"warning subshells not supported\n");
	else if (opt == ERROR_UNSUPPORTED_FEATURE_HEREDOC)
		ft_print_error("minishell: ", code, "warning heredocs not supported\n");
}

int	ft_tokenizer_error(int opt, t_tokenizer *tz)
{
	int	code;

	code = ERROR;
	if (opt == ERROR_UNKNOWN)
		handle_error_unknown(tz, code);
	else if (opt == ERROR_UNSUPPORTED_FEATURE)
		handle_error_unsupported_feature(tz, code);
	else if (opt == ERROR_GET_NEXT_LINE)
		exit (0);
	else
		handle_specific_errors(opt, code);
	return (ERROR);
}
