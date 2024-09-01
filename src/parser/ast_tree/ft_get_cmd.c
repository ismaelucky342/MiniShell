#include "../../../includes/minishell.h"

t_node_type	get_cmd(t_token *token_first, t_ast_node **head, t_cmd *cmd)
{
	int word_count;
	int i;

	i = 0;
	if (!cmd)
		return (ERROR);
	word_count = count_words(token_first);
	if (word_count == -1 || (word_count == 0 && !cmd))
	{
		if (word_count == 0)
			print_syntax_err(NULL);
		return (cmd_free(cmd), ERROR);
	}
	cmd->args = ft_calloc(word_count + 1, sizeof(char *));
	if (!cmd->args)
		return (err_pars("malloc", cmd, &token_first));
	while (token_first)
	{
		if (token_first->value)
			cmd->args[i++] = token_first->value;
		token_first->value = NULL;
		token_delete(&token_first);
	}
	*head = ft_ast_new_node();
	(*head)->type = CMD;
	(*head)->value = cmd;
	return (CMD);
}