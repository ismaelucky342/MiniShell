# include "../../includes/minishell.h"

int		ft_tree_build_error(t_astb *tool, int opt)
{
	if (opt == BAD_TOKEN)
	{
		if (tool->current_token->type == TOKEN_END_TOKEN)
			ft_printf_fd(2, "minishell: syntax error: unexpected end of file\n");
		else
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token \'%s\'\n",
				tool->current_token->value);
	}
	return (ERROR);
}
