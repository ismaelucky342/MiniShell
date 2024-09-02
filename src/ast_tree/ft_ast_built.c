# include "../../includes/minishell.h"

int		init_tool(t_astb *tool, int sloc)
{
	ft_bzero(tool, sizeof(t_astb));
	if (!(tool->ast_lexer = lexer__new(sloc)))
		return (ERROR);
	if ((tool->current_token = lexer__get_next_token(tool->ast_lexer)) == NULL)
		return (ERROR);
	if (!tool->current_token || tool->current_token->type == TOKEN_END_TOKEN)
	{
		lexer__del(&tool->ast_lexer);
		return (EMPTY);
	}
	tool->previous_token = NULL;
	tool->tree_possition = NULL;
	tool->ast_tree= NULL;
	return (SUCCESS);
}

t_ast_node	*ast_builder(int sloc)
{
	t_astb		tool;
	int			ret;

	ret = init_tool(&tool, sloc);
	if (ret == EMPTY)
		return (ast_builder(sloc));
	if (ret != ERROR && process(&tool) != ERROR)
	{
		lexer__del(&tool.ast_lexer);
		return (tool.ast_tree);
	}
	lexer__del(&tool.ast_lexer);
	return (NULL);
}