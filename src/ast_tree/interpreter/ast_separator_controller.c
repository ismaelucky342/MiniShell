/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_sep_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 02:46:55 by tharchen          #+#    #+#             */
/*   Updated: 2024/09/06 17:09:08 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 RUN THE LEFT CHILD OF THE DBL_AND NODE THEN WAIT FOR ITS END
 IF THE LEFT CHILD SUCCEEDED SO RUN THE RIGHT CHILD AND WAIT FOR ITS END
 RETURN THE RETURN VALUE OF THE LEFT CHILD IF IT HAS FAILED ELSE IT RETURN
 THE RETURN OF THE RIGHT CHILD ELSE
*/

int	ast_dbl_and_handle(t_ast_node *cmd_sep)
{
	int	sloc;

	sloc = ast_controller(cmd_sep->left);
	if (sloc == 0)
		sloc = ast_controller(cmd_sep->right);
	return (WEXITSTATUS(sloc));
}

/*
 THIS FUNCTION RUN THE LEFT CHILD OF THE DBL_OR NODE THEN WAIT FOR ITS END
 IF THE LEFT CHILD FAILED SO RUN THE RIGHT CHILD AND WAIT FOR ITS END
 RETURN THE RETURN VALUE OF THE LEFT CHILD IF IT HAS SUCCEEDED ELSE IT RETURN
 THE RETURN OF THE RIGHT CHILD ELSE
*/

int	ast_dbl_or_handle(t_ast_node *cmd_sep)
{
	int	sloc;

	sloc = ast_controller(cmd_sep->left);
	if (sloc != 0)
		sloc = ast_controller(cmd_sep->right);
	return (WEXITSTATUS(sloc));
}

/*
THIS FUNCTION RUN THE LEFT CHILD OF THE SEMICON NODE THEN WAIT FOR ITS END
IF THE RIGHT CHILD EXIST (NOT NULL) THEN RUN IT AND WAIT FOR ITS END
RETURN THE LAST RETURN LEFT OR RIGHT
*/

int	ast_semicon_handle(t_ast_node *cmd_sep)
{
	int	sloc;

	sloc = ast_controller(cmd_sep->left);
	if (cmd_sep->right)
		sloc = ast_controller(cmd_sep->right);
	return (sloc);
}

/*
THIS FUNCTION RUN THE GOOD FUNCTION TO HANDLE SEPARATORS.
ast_pipe_handle FOR PIPES
ast_dbl_and_handle FOR DBL_AND SEPARATOR
ast_dbl_or_handle FOR DBL_OR SEPARATOR
ast_semicon_handle FOR SEMICON SEPARATOR
RETURN ERROR IF THE NODE IS NOT A GOOD SEP
*/

int	ast_sep_controller(t_ast_node *sep)
{
	if (token__istype(sep->separators, TOKEN_PIPE))
		return (ast_pipe_handle(sep));
	else if (token__istype(sep->separators, TOKEN_LOGICAL_AND))
		return (ast_dbl_and_handle(sep));
	else if (token__istype(sep->separators, TOKEN_LOGICAL_OR))
		return (ast_dbl_or_handle(sep));
	else if (token__istype(sep->separators, TOKEN_SEMICOLON))
		return (ast_semicon_handle(sep));
	else
		return (ERROR);
}
