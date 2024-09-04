# include "../../includes/minishell.h"

int		process_call_next(t_astb *tool, t_ast_node **sep)
{
	if (ft_token_issep(tool->current_token))
	{
		*sep = node__new(SEPARATOR);
		if (add_token_into_node(tool, &(*sep)->separators, ASTSEPARATOR) == ERROR)
			return (ERROR);
		add_to_ast(tool, *sep);
		if (process(tool) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int		process(t_astb *tool)
{
	t_ast_node		*cmd;
	t_ast_node		*sep;

	if (tool->previous_token && (ft_token_istype(tool->previous_token, TOKEN_SEMICOLON) &&
		ft_token_iseot(tool->current_token)))
		return (SUCCESS);
	if (ft_token_issep(tool->current_token) || ft_token_iseot(tool->current_token))
		return (astb_error(tool, BAD_TOKEN));
	cmd = node__new(CMD);
	while (ft_token_isword(tool->current_token) ||
		ft_token_isword(tool->current_token))
	{
		if (ft_token_isword(tool->current_token))
		{
			if (add_token_into_node(tool, &cmd->redirections, ASTREDIR) == ERROR)
				return (ERROR);
			if (add_token_into_node(tool, &cmd->files, ASTWORDS) == ERROR)
				return (ERROR);
			continue ;
		}
		if (add_token_into_node(tool, &cmd->av, ASTWORDS) == ERROR)
			return (ERROR);
	}
	add_to_ast(tool, cmd);
	return (process_call_next(tool, &sep));
}