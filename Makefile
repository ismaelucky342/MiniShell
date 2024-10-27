G = \033[1;32m
Y = \033[1;33m
R = \033[0;31m
NC = \033[0m

NAME = minishell

VPATH	=	src/env/:src/expander/:src/parse/checker/:src/parse/Errors/:src/parse/heredoc/:src/parse/history/:src/parse/lexer/:src/parse/Multiple_Tools/:src/parse/tree/:src/parse/wildcards/:src/

SRC		=	enviroment.c \
			ft_env_get_value.c \
			ft_env_no_value.c \
			ft_remove_env.c \
			dictionary.c \
			expander.c \
			expand_types.c \
			ft_expand_env.c \
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
			tokenizer.c \
			retokenizer.c \
			cleanup.c \
			utils.c \
			ast_tree.c \
			ft_free_list.c \
			ft_free_redirections.c \
			ft_free_tree.c \
			wildcards.c \
			wildcards_utils.c \
			wildcards_files.c \
			ft_wdc_len.c \
			init.c \
			minishell.c \
			prompt.c \
			signals.c 

OBJ_DIR  = objects

INCLUDE = includes/minishell.h

OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

LIBFT = ./Libft/libft.a

all: $(NAME)
	@echo "	     $(G) ███$(R)╗$(G)   ███$(R)╗$(G) ██$(R)╗$(G) ███$(R)╗$(G)   ██$(R)╗$(G) ██$(R)╗$(G) ███████$(R)╗$(G) ██$(R)╗$(G)  ██$(R)╗$(G) ███████$(R)╗$(G) ██$(R)╗$(G)      ██$(R)╗$(G)     $(NC)"
	@echo "	     $(G) ████$(R)╗$(G) ████$(R)║$(G) ██$(R)║$(G) ████$(R)╗$(G)  ██$(R)║$(G) ██$(R)║$(G) ██$(R)╔════╝$(G) ██$(R)║$(G)  ██$(R)║$(G) ██$(R)╔════╝$(G) ██$(R)║$(G)      ██$(R)║$(G)     $(NC)"
	@echo "	     $(G) ██$(R)╔$(G)████$(R)╔$(G)██$(R)║$(G) ██$(R)║$(G) ██$(R)╔$(G)██$(R)╗$(G) ██$(R)║$(G) ██$(R)║$(G) ███████$(R)╗$(G) ███████$(R)║$(G) █████$(R)╗$(G)   ██$(R)║$(G)      ██$(R)║$(G)     $(NC)"
	@echo "	     $(G) ██$(R)║$(G)$(R)╚$(G)██$(R)╔╝$(G)██$(R)║$(G) ██$(R)║$(G) ██$(R)║╚$(G)██$(R)╗$(G)██$(R)║$(G) ██$(R)║ ╚════$(G)██$(R)║$(G) ██$(R)╔══$(G)██$(R)║$(G) ██$(R)╔══╝$(G)   ██$(R)║$(G)      ██$(R)║$(G)     $(NC)"
	@echo "	     $(G) ██$(R)║$(G) $(R)╚═╝$(G) ██$(R)║$(G) ██$(R)║$(G) ██$(R)║$(G) $(R)╚$(G)████$(R)║$(G) ██$(R)║$(G) ███████$(R)║$(G) ██$(R)║$(G)  ██$(R)║$(G) ███████$(R)╗$(G) ███████$(R)╗$(G) ███████$(R)╗$(G)$(NC)"
	@echo "	     $(G) $(R)╚═╝$(G)     $(R)╚═╝$(G) $(R)╚═╝$(G) $(R)╚═╝$(G)  $(R)╚═══╝$(G) $(R)╚═╝$(G) $(R)╚══════╝$(G) $(R)╚═╝$(G)  $(R)╚═╝$(G) $(R)╚══════╝$(G) $(R)╚══════╝$(G) $(R)╚══════╝$(G)$(NC)"
	@echo "	     			   $(G)dgomez-l $(Y)/ $(R)ismherna$(NC)"
	@echo "	     			NEVER GONNA GIVE YOU PIPE"

print:
	@echo "$(Y)--------------------------------------- Compiling  Minishell ---------------------------------------$(NC)"

$(NAME): $(LIBFT) $(OBJ_DIR) print $(OBJ) includes/minishell.h
	@printf "%-147s\r" "                                                                                                              "
	@$(CC) $(CFLAGS) $(OBJ) -I $(INCLUDE) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(G)----------------------------------- Minishell Finished Compiling -----------------------------------$(NC)\n"
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"
	@echo "$(G)---------------------------------------- Minishell Is Ready ----------------------------------------$(NC)"
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)\n"

$(LIBFT):
	@echo "$(Y)------------------------------------ Compiling Libft With Bonus ------------------------------------$(NC)"
	@make -sC ./Libft CFLAGS="$(CFLAGS)"

$(OBJ_DIR):
	@echo "$(R)---------------------------------- Object Directory Doesn't Exist ----------------------------------$(NC)"
	@echo "$(Y)------------------------------------ Creating Objects Directory ------------------------------------$(NC)"
	@mkdir -p $(OBJ_DIR)
	@echo "$(G)-------------------------------------- Objects Directory Done --------------------------------------\n$(NC)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c -o $@ $<
	@printf "%-147s\r" ">Minishell compiling: ""$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<"

clean:
	@make -sC ./Libft fclean
	@rm -rf $(OBJ_DIR)
	@echo "$(R)----------------------------------------- Objects  Cleaned -----------------------------------------$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(R)---------------------------------------- Minishell Is Clean ----------------------------------------\n$(NC)"

re: fclean all

.DEFAULT_GOAL: all

.PHONY: all clean fclean re