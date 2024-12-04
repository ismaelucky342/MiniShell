# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 14:15:58 by dgomez-l          #+#    #+#              #
#    Updated: 2024/12/04 16:26:00 by dgomez-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

G = \033[1;32m
Y = \033[1;33m
R = \033[0;31m
NC = \033[0m

NAME = minishell

VPATH	=	src/:\
			src/env/:\
			src/exec/:\
			src/exec/builtins/:\
			src/exec/find_path/:\
			src/exec/pipes/:\
			src/exec/logic/:\
			src/expander/:\
			src/parse/:\
			src/parse/checker/:\
			src/parse/heredoc/:\
			src/parse/history/:\
			src/parse/lexer/:\
			src/parse/tree/:\
			src/parse/wildcards/:\
			src/parse/errors/:\
			src/parse/multiple_tools/:

SRC		=	enviroment.c \
			ft_env_get_value.c \
			ft_env_no_value.c \
			ft_remove_env.c \
			cd.c \
			echo.c \
			env.c \
			exit.c \
			export.c \
			pwd.c \
			unset.c \
			find_path.c \
			logic_interpreter.c \
			exec_first.c \
			exec_last.c \
			exec_mid.c \
			pipe_interpreter.c \
			exec_builtins.c \
			exec_single.c \
			exec_ve.c \
			execution.c \
			isbuiltin.c \
			dictionary.c \
			expand_types.c \
			expander.c \
			ft_expand_env.c \
			ft_hitman.c \
			heredoc_expander.c \
			wildcard_expand.c \
			check_heredoc.c \
			checker_errors.c \
			checker.c \
			Errors_1.c \
			Errors_2.c \
			heredoc.c \
			input.c \
			history.c \
			ft_remove_quotes.c \
			retokenizer.c \
			tokenizer.c \
			cleanup.c \
			utils.c \
			ast_tree.c \
			ft_free_list.c \
			ft_free_redirections.c \
			ft_free_tree.c \
			ft_wdc_len.c \
			wildcards_files.c \
			wildcards_utils.c \
			wildcards.c \
			init.c \
			minishell.c \
			prompt.c \
			signals.c 
			

OBJ_DIR  = objects

INCLUDE = /includes/minishell.h

OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize="address"

LIBFT = ./Libft/libft.a

clear:
	clear

all: clear $(LIBFT) $(NAME) title_print

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ) includes/minishell.h
	@printf "%-147s\r" "                                                                                                              "
	@$(CC) $(CFLAGS) $(OBJ) -I $(INCLUDE) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(G)----------------------------------- Minishell Finished Compiling -----------------------------------$(NC)\n"

$(LIBFT):
	@echo "$(Y)------------------------------------ Compiling Libft With Bonus ------------------------------------$(NC)"
	@make -sC ./Libft CFLAGS="$(CFLAGS)"

$(OBJ_DIR):
	@echo "$(Y)--------------------------------------- Compiling  Minishell ---------------------------------------$(NC)"
	@echo "$(R)---------------------------------- Object Directory Doesn't Exist ----------------------------------$(NC)"
	@echo "$(Y)------------------------------------ Creating Objects Directory ------------------------------------$(NC)"
	@mkdir -p $(OBJ_DIR)
	@echo "$(G)-------------------------------------- Objects Directory Done --------------------------------------\n$(NC)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c -o $@ $<
	@printf "%-147s\r" ">Minishell compiling: ""$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<"

clean: clear
	@make -sC ./Libft fclean
	@rm -rf $(OBJ_DIR)
	@echo "$(R)----------------------------------------- Objects  Cleaned -----------------------------------------$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(R)---------------------------------------- Minishell Is Clean ----------------------------------------\n$(NC)"

re: fclean $(NAME) title_print

title_print:
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"
	@echo "$(G)---------------------------------------- Minishell Is Ready ----------------------------------------$(NC)"
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)\n"
	@echo "	    $(G) ███$(R)╗$(G)   ███$(R)╗$(G) ██$(R)╗$(G) ███$(R)╗$(G)   ██$(R)╗$(G) ██$(R)╗$(G) ███████$(R)╗$(G) ██$(R)╗$(G)  ██$(R)╗$(G) ███████$(R)╗$(G) ██$(R)╗$(G)      ██$(R)╗$(G)     $(NC)"
	@echo "	    $(G) ████$(R)╗$(G) ████$(R)║$(G) ██$(R)║$(G) ████$(R)╗$(G)  ██$(R)║$(G) ██$(R)║$(G) ██$(R)╔════╝$(G) ██$(R)║$(G)  ██$(R)║$(G) ██$(R)╔════╝$(G) ██$(R)║$(G)      ██$(R)║$(G)     $(NC)"
	@echo "	    $(G) ██$(R)╔$(G)████$(R)╔$(G)██$(R)║$(G) ██$(R)║$(G) ██$(R)╔$(G)██$(R)╗$(G) ██$(R)║$(G) ██$(R)║$(G) ███████$(R)╗$(G) ███████$(R)║$(G) █████$(R)╗$(G)   ██$(R)║$(G)      ██$(R)║$(G)     $(NC)"
	@echo "	    $(G) ██$(R)║$(G)$(R)╚$(G)██$(R)╔╝$(G)██$(R)║$(G) ██$(R)║$(G) ██$(R)║╚$(G)██$(R)╗$(G)██$(R)║$(G) ██$(R)║ ╚════$(G)██$(R)║$(G) ██$(R)╔══$(G)██$(R)║$(G) ██$(R)╔══╝$(G)   ██$(R)║$(G)      ██$(R)║$(G)     $(NC)"
	@echo "	    $(G) ██$(R)║$(G) $(R)╚═╝$(G) ██$(R)║$(G) ██$(R)║$(G) ██$(R)║$(G) $(R)╚$(G)████$(R)║$(G) ██$(R)║$(G) ███████$(R)║$(G) ██$(R)║$(G)  ██$(R)║$(G) ███████$(R)╗$(G) ███████$(R)╗$(G) ███████$(R)╗$(G)$(NC)"
	@echo "	    $(G) $(R)╚═╝$(G)     $(R)╚═╝$(G) $(R)╚═╝$(G) $(R)╚═╝$(G)  $(R)╚═══╝$(G) $(R)╚═╝$(G) $(R)╚══════╝$(G) $(R)╚═╝$(G)  $(R)╚═╝$(G) $(R)╚══════╝$(G) $(R)╚══════╝$(G) $(R)╚══════╝$(G)$(NC)"
	@echo "	                                $(G)dgomez-l $(Y)/ $(R)ismherna$(NC)"
	@echo "	                             NEVER GONNA GIVE YOU PIPE"

norm: clear
	@norminette $(find src/) | grep -v OK\! | grep -v GLOBAL_VAR_DETECTED | grep -v WRONG_SCOPE_COMMENT > _test_norm_output.txt
	@cat _test_norm_output.txt

.DEFAULT_GOAL= all

.PHONY: all clean fclean re clear title_print
