# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgomez-l <dgomez-l@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 14:15:58 by dgomez-l          #+#    #+#              #
#    Updated: 2024/12/10 20:24:56 by dgomez-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

G = \033[1;32m
Y = \033[1;33m
R = \033[0;31m
NC = \033[0m

NAME = minishell

VPATH	=	src/:\
			src/enviroment/:\
			src/execute/:\
			src/builtins/:\
			src/tokenizer/:\
			src/heredoc/:\
			src/history/:\
			src/utils/:\
			src/wildcards/:\
			src/expander/:\
			src/ast_tree/:\
			src/signals_and_errors/:

SRC		=	enviroment/enviroment.c \
			enviroment/get_env.c \
			enviroment/remove_env.c \
			execute/parse_exec_monitor.c \
			execute/exec_errors.c \
			execute/exec_utils.c \
			execute/execute.c \
			execute/get_tokens.c \
			execute/logic_expansion.c \
			execute/path_finder.c \
			execute/pipe_interpreter.c \
			execute/redirect_utils.c \
			execute/single_cmd.c \
			builtins/cd.c \
			builtins/echo.c \
			builtins/exit.c \
			builtins/export.c \
			builtins/pwd.c \
			builtins/unset.c \
			builtins/builtins_utils.c \
			tokenizer/tokenizer.c \
			tokenizer/ft_free_token.c \
			tokenizer/quotes.c \
			tokenizer/retokenizer.c \
			heredoc/heredoc.c \
			heredoc/heredoc_checker.c \
			heredoc/heredoc_monitor.c \
			heredoc/ft_create_heredoc.c \
			history/history.c \
			history/history_file.c \
			wildcards/wildcards.c \
			wildcards/wildcards_utils.c \
			expander/dictionary.c \
			expander/env_expander.c \
			expander/expand_list.c \
			expander/heredoc_expander.c \
			expander/quotes_expander.c \
			expander/str_expander.c \
			expander/wildcards_expander.c \
			ast_tree/ast_tree.c \
			ast_tree/ft_free_ast_tree.c \
			ast_tree/ft_free_array.c \
			freedom.c \
			ft_prompt.c \
			init.c \
			main.c \
			signals_and_errors/errors_1.c \
			signals_and_errors/errors_2.c \
			signals_and_errors/signals.c \
			signals_and_errors/syntax_checker.c \
			signals_and_errors/tremios_control.c

OBJ_DIR  = objects

INCLUDE = /includes/minishell.h

OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

LIBFT = ./Libft/libft.a

clear:
	clear

all: clear $(LIBFT) $(NAME) title_print

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ) includes/minishell.h
	@printf "%-183s\r" ""
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
	@printf "%-183s\r" ">Minishell compiling: ""$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<"

clean: clear
	@make -sC ./Libft fclean
	@rm -rf $(OBJ_DIR)
	@find src -type f -name '*.o' -delete
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
