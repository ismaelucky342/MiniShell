#include "../../../includes/minishell.h"

t_ast_node *create_operator_node(t_token_type op_type)
{
    t_ast_node *node;

    node = ft_ast_new_node();
    if (!node)
        return (NULL);

    if (op_type == T_AND)
        node->type = AND;
    else if (op_type == T_OR)
        node->type = OR;

    node->children = malloc(sizeof(t_ast_node *) * 2);
    if (!node->children)
    {
        free(node);
        return (NULL);
    }

    node->children_count = 2;
    node->children[0] = NULL;
    node->children[1] = NULL;

    return (node);
}

t_node_type process_left_right_nodes(t_token *tokens, t_token *op_token, t_ast_node **node)
{
    t_node_type return_value;

    return_value = split_by_pipe(tokens, &((*node)->children[0]));
    if (return_value == ERROR)
        return (ERROR);

    return_value = split_by_pipe(op_token, &((*node)->children[1]));
    if (return_value == ERROR)
    {
        node_tree_delete(*node, (*node)->type);
        return (ERROR);
    }

    return ((*node)->type);
}

t_node_type split_by_operator(t_token *tokens, t_ast_node **head)
{
    t_token *op_token;
    t_ast_node *node;
    t_node_type result;

    op_token = get_operator(tokens);
    if (!op_token)
        return (split_by_pipe(tokens, head));

    node = create_operator_node(op_token->type);
    if (!node)
        return (ERROR);

    op_token = token_split(op_token, -1);

    result = process_left_right_nodes(tokens, op_token, &node);
    if (result == ERROR)
    {
        free(node->children);
        free(node);
        return (ERROR);
    }

    *head = node;
    return (result);
}
