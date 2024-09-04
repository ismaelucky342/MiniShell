#include "../../../includes/minishell.h"

int ft_tokenizer_error(int opt, t_tokenizer *tz)
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
        return 0; 
    else
        ft_printf_fd(2, "minishell: invalid character \'%c\' (%#x)\n",
            tz->current_char, tz->current_char);
    return (ERROR);
}

int			unsupported_feature(t_tokenizer *tz, int *token_type, char curr, char next)
{
	if (curr == '(' && !(*token_type = TYPE_ERROR))
		ft_tokenizer_error(ERROR_UNSUPPORTED_FEATURE_SUBSHELL, tz);
	else if (curr == ')' && !(*token_type = TYPE_ERROR))
		ft_tokenizer_error(ERROR_UNSUPPORTED_FEATURE_SUBSHELL, tz);
	else if (tz->line_length > 1 && curr == '<' && next == '<' &&
		!(*token_type = TYPE_ERROR))
		ft_tokenizer_error(ERROR_UNSUPPORTED_FEATURE_HEREDOC, tz);
	else if (curr == '&' && !(*token_type = TYPE_ERROR))
		ft_tokenizer_error(ERROR_UNSUPPORTED_FEATURE, tz);
	else
		return (0);
	return (1);
}

int			ft_tokenizer_deftoken_double(t_tokenizer *tz, int *len, char curr, char next)
{
	if (tz->line_length > 1 && curr == '&' && next == '&' && (*len = 2))
		return (TYPE_LOGICAL_AND);
	if (tz->line_length > 1 && curr == '|' && next == '|' && (*len = 2))
		return (TYPE_LOGICAL_OR);
	if (tz->line_length > 1 && curr == '>' && next == '>' && (*len = 2))
		return (TYPE_REDIR_OUTPUT);
	return (0);
}

int			ft_tokenizer_isdefined_token(t_tokenizer *tz, int adv)
{
	int		type_len[2];
	char	current_next[2];

	if (!tz->current_line && (type_len[1] = 0))
		return (TYPE_ERROR);
	current_next[0] = tz->current_char;
	current_next[1] = tz->line_length > 1 ? tz->current_line[tz->current_position + 1] : 0;
	if ((type_len[0] = ft_tokenizer_deftoken_double(tz, &type_len[1], current_next[0], current_next[1])) == TYPE_ERROR)
	{
		if (unsupported_feature(tz, &type_len[0], current_next[0], current_next[1]))
			return (type_len[0]);
		else if (current_next[0] == '<' && (type_len[1] = 1))
			type_len[0] = TYPE_REDIR_INPUT;
		else if (current_next[0] == '>' && (type_len[1] = 1))
			type_len[0] = TYPE_REDIR_OUTPUT;
		else if (type_len[0] == TYPE_ERROR && current_next[0] == '|' && (type_len[1] = 1))
            type_len[0] = TYPE_PIPE;
		else if (current_next[0] == ';' && (type_len[1] = 1))
			type_len[0] = TYPE_SEMICOLON;
		else if (!type_len[0])
			return (TYPE_NONE);
	}
	if (type_len[0] != TYPE_ERROR && adv == FOREACH_ADVANCE_ITERATOR)
		ft_tokenizer_advance(tz, type_len[1]);
	return (type_len[0]);
}
