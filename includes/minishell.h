/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:07:41 by dgomez-l          #+#    #+#             */
/*   Updated: 2024/09/07 16:52:25 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include "AST.h"
# include "Tokenizer.h"
# include "signal.h"
# include "tokens.h"
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <readline/readline.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>

# ifndef LINE_MAX
#  define LINE_MAX 4096
# endif

# define BUILTINS 7

/*----------EXECUTION ERRORS-----------*/

typedef enum e_error_value
{
	SUCCESS,
	ERROR,
	EMPTY
}			t_error_value;

typedef struct builtins
{
	char	*name;
	int		(*f)(int argc, char **args, int out);
}			t_builtins;

/*-------------------COLORS STRUCT----------------*/

# define COLOR_RESET "\033[0m"

# define COLOR_BACKGROUND_BLACK "\033[40m"
# define COLOR_BACKGROUND_RED "\033[41m"
# define COLOR_BACKGROUND_GREEN "\033[42m"
# define COLOR_BACKGROUND_YELLOW "\033[43m"
# define COLOR_BACKGROUND_BLUE "\033[44m"
# define COLOR_BACKGROUND_MAGENTA "\033[45m"
# define COLOR_BACKGROUND_CYAN "\033[46m"
# define COLOR_BACKGROUND_WHITE "\033[47m"
# define COLOR_BACKGROUND_GRAY "\033[100m"

# define COLOR_BLACK_TEXT "\033[30m"
# define COLOR_RED_TEXT "\033[31m"
# define COLOR_GREEN_TEXT "\033[32m"
# define COLOR_YELLOW_TEXT "\033[33m"
# define COLOR_BLUE_TEXT "\033[34m"
# define COLOR_MAGENTA_TEXT "\033[35m"
# define COLOR_CYAN_TEXT "\033[36m"
# define COLOR_WHITE_TEXT "\033[37m"
# define COLOR_GRAY_TEXT "\033[90m"

# define COLOR_BOLD_BLACK_TEXT "\033[30;01m"
# define COLOR_BOLD_RED_TEXT "\033[31;01m"
# define COLOR_BOLD_GREEN_TEXT "\033[32;01m"
# define COLOR_BOLD_YELLOW_TEXT "\033[33;01m"
# define COLOR_BOLD_BLUE_TEXT "\033[34;01m"
# define COLOR_BOLD_MAGENTA_TEXT "\033[35;01m"
# define COLOR_BOLD_CYAN_TEXT "\033[36;01m"
# define COLOR_BOLD_WHITE_TEXT "\033[37;01m"
# define COLOR_BOLD_GRAY_TEXT "\033[90;01m"

/*--------------------ENV FILES---------------*/
void		ft_env2hashtable(t_mem_context *ctx, char **env, t_hashtable *hashtable, int array_len);
t_hashtable	*ft_create_envhash(t_mem_context *ctx, char **env);
void		ft_print_env(t_hashtable *env_hashtable, int is_export);
void		free_env_hashtable(t_hashtable *hashtable, int array_len);
const char	*ft_hashtable_get(t_hashtable *hashtable, const char *key);
void		process_env_variable(t_mem_context *ctx, char **env, t_hashtable *hashtable,
				int array_len);

void		insert_into_hashtable(t_mem_context *ctx, char *key, char *value,
				t_hashtable *hashtable, int array_len);
void		add_new_element(t_mem_context *ctx, char *key, char *value, t_hashtable *hashtable,
				int hash_index);

/*--------EXECUTION FILES--------*/
/*
int			xecho(int argc, char **args, int out);
int			xpwd(int argc, char **args, int out);
int			xexit(int argc, char **args, int out);
int			xcd(int argc, char **args, int out);
char		**env_to_arr(t_hashtable *hashtable);
void		sig_exec(int signo);
char		**convert_to_arr(t_token *args, int ac);
char		**check_cmd(t_ast_node *cmd, int *ac, int *type);
int			launch(t_ast_node *cmd, char **av);
int			execute_fork(t_ast_node *cmd, int out);
int			execute_simple(t_ast_node *cmd);
char		*get_path(char *command, int *err);
*/

#endif
