# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 14:15:58 by dgomez-l          #+#    #+#              #
#    Updated: 2024/12/18 19:57:57 by ismherna         ###   ########.fr        #
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

SRC		=	enviroment.c \
			get_env.c \
			remove_env.c \
			parse_exec_monitor.c \
			exec_errors.c \
			exec_utils.c \
			execute.c \
			get_tokens.c \
			logic_expansion.c \
			path_finder.c \
			pipe_interpreter.c \
			redirect_utils.c \
			single_cmd.c \
			cd.c \
			echo.c \
			exit.c \
			export.c \
			pwd.c \
			unset.c \
			builtins_utils.c \
			tokenizer.c \
			ft_free_token.c \
			quotes.c \
			retokenizer.c \
			heredoc.c \
			heredoc_checker.c \
			heredoc_monitor.c \
			ft_create_heredoc.c \
			history.c \
			history_file.c \
			wildcards.c \
			wildcards_utils.c \
			dictionary.c \
			env_expander.c \
			expand_list.c \
			heredoc_expander.c \
			quotes_expander.c \
			str_expander.c \
			wildcards_expander.c \
			ast_tree.c \
			ft_free_ast_tree.c \
			ft_free_array.c \
			errors_1.c \
			errors_2.c \
			signals.c \
			syntax_checker.c \
			tremios_control.c \
			freedom.c \
			ft_prompt.c \
			init.c \
			main.c 

OBJ_DIR  = objects

INCLUDE = /includes/minishell.h

OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

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
	@echo "$(G)\t\t\t\t ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⣤⣶⣿⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
\t\t\t\t ⠀⠀⢠⢲⢀⡶⡄⣀⠀⠀⠀⢠⣾⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
\t\t\t\t ⡠⣄⠘⡄⡿⠀⡿⡷⡇⠀⢠⣯⣿⠿⢿⣿⡿⣿⣽⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀\n\
\t\t\t\t ⠙⢌⠒⠇⠃⣸⣽⡀⢧⠀⣿⣿⠁⠀⠀⠉⠻⢿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀\n\
\t\t\t\t ⠀⠈⢳⡰⠾⠋⠹⠻⣿⡇⢹⡿⣤⣀⡀⠀⠀⠀⠈⠛⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
\t\t\t\t ⠀⠀⠀⠱⡄⠀⠀⠓⡰⠁⠸⡇⢱⣾⣿⡦⢤⣲⣶⡾⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
\t\t\t\t ⠀⠀⠀⠀⢇⠀⠀⠀⡇⠀⣀⣇⠀⠉⠉⠀⠘⠻⢿⣧⡤⠤⣀⠀⠀⠀⠀⠀⠀⠀\n\
\t\t\t\t ⠀⠀⠀⠀⢸⠀⠀⠀⢳⠋⠓⢼⣶⠞⠛⠒⠲⣶⠏⠻⣷⣿⣦⣱⡀⠀⠀⠀⠀⠀\n\
\t\t\t\t ⠀⠀⠀⠀⢸⠀⡀⠀⠈⢇⠀⠀⠉⠳⢦⡴⠞⠸⠀⠀⠈⢿⡟⢏⡇⠀⠀⠀⠀⠀\n\
\t\t\t\t ⠀⠀⠀⠀⡇⠀⡇⠀⠀⠘⣆⠀⠀⠀⠀⠙⠯⣅⡀⠀⠀⢸⠃⠈⢇⠀⠀⠀⠀⠀\n\
\t\t\t\t ⠀⠀⠀⢸⠁⠀⡇⠀⠀⠀⠸⡄⠀⠀⠀⠀⠀⠀⠉⠒⠚⠁⠀⠀⠼⡆⠀⠀⠀⠀\n\
\t\t\t\t ⠀⠀⠀⢸⠀⠀⢱⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡄⠹⡄⠀⠀⠀\n\
\t\t\t\t ⠀⠀⠀⠘⡄⠀⠀⠀⠀⠀⠐⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⡇⠀⢣⠀⠀⠀\n\
\t\t\t\t ⠀⠀⠀⠀⠘⢧⠀⠀⠀⢀⣠⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⢸⠀⠀⠀\n\
\t\t\t\t ⠀⠀⠀⠀⠀⠀⠉⠉⢫⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⠀⠈⡄⠀⠀\n\
\t\t\t\t ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⡂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡄⠀⡇⠀⠀\n\
\t\t\t\t ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣧⣤⣿⠀⠀\n\
\t\t\t\t ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⢻⠀⠈⠢⡀\n\
\t\t\t\t ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣀⠀⣀⣀⠀⠀⠀⠀⠀⠀⠀⣀⡤⠃⠘⡄⡤⡄⢱\n\
\t\t\t\t ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠀⠀⠀⠀⠀⠤⠐⠒⠋⠀⠀⠀⠱⠇⢸⢸$(NC)"
	@echo "	    $(G) ███$(R)╗$(G)   ███$(R)╗$(G) ██$(R)╗$(G) ███$(R)╗$(G)   ██$(R)╗$(G) ██$(R)╗$(G) ███████$(R)╗$(G) ██$(R)╗$(G)  ██$(R)╗$(G) ███████$(R)╗$(G) ██$(R)╗$(G)      ██$(R)╗$(G)     $(NC)"
	@echo "	    $(G) ████$(R)╗$(G) ████$(R)║$(G) ██$(R)║$(G) ████$(R)╗$(G)  ██$(R)║$(G) ██$(R)║$(G) ██$(R)╔════╝$(G) ██$(R)║$(G)  ██$(R)║$(G) ██$(R)╔════╝$(G) ██$(R)║$(G)      ██$(R)║$(G)     $(NC)"
	@echo "	    $(G) ██$(R)╔$(G)████$(R)╔$(G)██$(R)║$(G) ██$(R)║$(G) ██$(R)╔$(G)██$(R)╗$(G) ██$(R)║$(G) ██$(R)║$(G) ███████$(R)╗$(G) ███████$(R)║$(G) █████$(R)╗$(G)   ██$(R)║$(G)      ██$(R)║$(G)     $(NC)"
	@echo "	    $(G) ██$(R)║$(G)$(R)╚$(G)██$(R)╔╝$(G)██$(R)║$(G) ██$(R)║$(G) ██$(R)║╚$(G)██$(R)╗$(G)██$(R)║$(G) ██$(R)║ ╚════$(G)██$(R)║$(G) ██$(R)╔══$(G)██$(R)║$(G) ██$(R)╔══╝$(G)   ██$(R)║$(G)      ██$(R)║$(G)     $(NC)"
	@echo "	    $(G) ██$(R)║$(G) $(R)╚═╝$(G) ██$(R)║$(G) ██$(R)║$(G) ██$(R)║$(G) $(R)╚$(G)████$(R)║$(G) ██$(R)║$(G) ███████$(R)║$(G) ██$(R)║$(G)  ██$(R)║$(G) ███████$(R)╗$(G) ███████$(R)╗$(G) ███████$(R)╗$(G)$(NC)"
	@echo "	    $(G) $(R)╚═╝$(G)     $(R)╚═╝$(G) $(R)╚═╝$(G) $(R)╚═╝$(G)  $(R)╚═══╝$(G) $(R)╚═╝$(G) $(R)╚══════╝$(G) $(R)╚═╝$(G)  $(R)╚═╝$(G) $(R)╚══════╝$(G) $(R)╚══════╝$(G) $(R)╚══════╝$(G)$(NC)"
	@echo "	                                $(G)dgomez-l $(Y)/ $(R)ismherna$(NC)"
	@echo "	                             $(Y)NEVER GONNA GIVE YOU PIPE$(NC)\n"
norm: clear
	@norminette $(find src/) | grep -v OK\!
	@cat _test_norm_output.txt

.DEFAULT_GOAL= all

.PHONY: all clean fclean re clear title_print
