/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:50:53 by ismherna          #+#    #+#             */
/*   Updated: 2024/11/12 10:54:32 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
// Asigna el tipo de redirección basado en el símbolo del token
static void	assign_redirection_type(t_list *token_list, t_list **tmp)
{
	if (ft_strncmp("<", ((t_token *)token_list->data)->str, 2) == 0)
		((t_redirection_token *)(*tmp)->data)->type = INFILE_MASK;
	else if (ft_strncmp(">", ((t_token *)token_list->data)->str, 2) == 0)
		((t_redirection_token *)(*tmp)->data)->type = OUTFILE_MASK;
	else if (ft_strncmp("<<", ((t_token *)token_list->data)->str, 3) == 0)
		((t_redirection_token *)(*tmp)->data)->type = HEREDOC_MASK;
	else if (ft_strncmp(">>", ((t_token *)token_list->data)->str, 3) == 0)
		((t_redirection_token *)(*tmp)->data)->type = CONCATOUT_MASK;
}

// Añade información de archivo de redirección al nodo actual
static int	add_file_info(t_list *token_list, t_tree_node *current)
{
	t_list	*tmp;

	if (!token_list->next) // Sin archivo después de redirección
		return (KO);

	// Busca el último elemento en la lista de redirecciones o crea uno nuevo
	tmp = current->redir_list;
	while (tmp && tmp->next)
		tmp = tmp->next;

	if (tmp) {
		tmp->next = ft_calloc(1, sizeof(t_list));
		if (!tmp->next)
			return (ERROR_MEMORY);
		tmp = tmp->next;
	} else {
		current->redir_list = ft_calloc(1, sizeof(t_list));
		if (!current->redir_list)
			return (ERROR_MEMORY);
		tmp = current->redir_list;
	}

	// Asigna el nombre del archivo y tipo de redirección
	tmp->data = ft_calloc(1, sizeof(t_redirection_token));
	if (!tmp->data)
		return (ERROR_MEMORY);
	((t_redirection_token *)tmp->data)->name
		= ft_strdup(((t_token *)token_list->next->data)->str);
	assign_redirection_type(token_list, &tmp);
	return (OK);
}

// Cuenta el número de argumentos hasta encontrar un PIPE
static int	ft_count_args(t_list *begin)
{
	t_token	*tkn;
	int		res = 0;

	while (begin) {
		tkn = begin->data;
		if (tkn->type == PIPE)
			break;
		if (tkn->type >= ARG)
			++res;
		begin = begin->next;
	}
	return (res);
}

// Gestiona cada token en la lista, agregándolo al nodo AST según su tipo
static int	fill_management(t_list **bgn, t_tree_node **current, t_tree_node **p_curr, int *i)
{
	if (((t_token *)(*bgn)->data)->type >= ARG) {
		(*current)->args[(*i)++] = ft_strdup(((t_token *)(*bgn)->data)->str);
	} else if (((t_token *)(*bgn)->data)->type == FILE_REDIR) {
		if (add_file_info((*bgn), (*current)))
			return (KO);
		(*bgn) = (*bgn)->next;
	} else if (((t_token *)(*bgn)->data)->type == PIPE) {
		if (!(*bgn)->next || ((t_token *)(*bgn)->next->data)->type == PIPE)
			return (KO);  // Error si hay PIPE consecutivos o al final

		(*current) = ft_calloc(1, sizeof(t_tree_node));
		if (!(*current))
			return (ERROR_MEMORY);
		(*p_curr)->next = (*current);  // Conecta el nodo nuevo
		(*p_curr) = (*current);
		(*current)->args = ft_calloc(ft_count_args((*bgn)->next) + 1, sizeof(char *));
		if (!(*current)->args)
			return (ERROR_MEMORY);
		(*i) = 0;
	}
	return (OK);
}

// Función principal para construir el AST a partir de una lista de tokens
int	ft_fill_list(t_list *begin, t_ast_tree *tree_node)
{
	t_token		*tkn;
	t_tree_node	*current;
	t_tree_node	*p_curr;
	int			ctr[2];

	current = ft_calloc(1, sizeof(t_tree_node));
	if (!current)
		return (ERROR_MEMORY);

	tree_node->cmd_list = current;
	p_curr = current;
	current->args = ft_calloc(ft_count_args(begin) + 1, sizeof(char *));
	if (!current->args)
		return (ERROR_MEMORY);
	tkn = begin->data;
	if (tkn->type == PIPE)  // Si empieza con un PIPE, es un error de sintaxis
		return (KO);
	ctr[0] = 0;  // Inicializa el índice para los argumentos
	while (begin) {
		ctr[1] = fill_management(&begin, &current, &p_curr, &ctr[0]);
		if (ctr[1])  // Si fill_management devuelve un error
			return (ctr[1]);
		begin = begin->next;
	}
	return (OK);
}
