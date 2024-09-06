# include "../../includes/minishell.h"

int process_call_next(t_astb *tool, t_ast_node **sep)
{
    if (ft_token_issep(tool->current_token))
    {
        *sep = ft_node_new(SEPARATOR); // Use ft_node_new to create a new node
        if (*sep == NULL)
            return (ERROR); // Ensure node creation was successful

        insert_node(tool, *sep); // Insert the separator node into the AST
        if (process(tool) == ERROR)
            return (ERROR);
    }
    return (SUCCESS);
}

int process(t_astb *tool)
{
    t_ast_node *cmd;
    t_ast_node *sep;

    if (tool->previous_token && (ft_token_istype(tool->previous_token, TOKEN_SEMICOLON) &&
        ft_token_iseot(tool->current_token)))
        return (SUCCESS);
    if (ft_token_issep(tool->current_token) || ft_token_iseot(tool->current_token))
        return (ft_tree_build_error(tool, BAD_TOKEN));

    cmd = ft_node_new(CMD); // Create a new CMD node
    if (cmd == NULL)
        return (ERROR); // Ensure node creation was successful

    while (ft_token_isword(tool->current_token) ||
           ft_token_isredir(tool->current_token))
    {
        if (ft_token_isredir(tool->current_token))
        {
            // Assuming you need to manage redirections and files
            // Insert or handle redirections and files appropriately
            // Here you would need to correctly set up and insert nodes for redirections and files
            continue;
        }
        // Handle arguments (av)
        // You need to create and add nodes to cmd->av
    }

    insert_node(tool, cmd); // Insert the command node into the AST
    return (process_call_next(tool, &sep));
}
