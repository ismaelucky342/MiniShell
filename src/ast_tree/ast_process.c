# include "../../includes/minishell.h"

int		process_call_next(t_astb *tool, t_ast_node **sep)
{
	if (token__issep(tool->current_token))
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

	if (tool->previous_token && (token__istype(tool->previous_token, TOKEN_SEMICOLON) &&
		token__iseot(tool->current_token)))
		return (SUCCESS);
	if (token__issep(tool->current_token) || token__iseot(tool->current_token))
		return (astb_error(tool, BAD_TOKEN));
	cmd = node__new(CMD);
	while (token__isword(tool->current_token) ||
		token__isredir(tool->current_token))
	{
		if (token__isredir(tool->current_token))
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