GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m

NAME = minishell

SRC		=	src/env/enviroment.c \
			src/env/ft_env_get_value.c \
			src/env/ft_env_no_value.c \
			src/env/ft_remove_env.c \
			src/expander/dictionary.c \
			src/expander/expander.c \
			src/expander/expand_types.c \
			src/expander/ft_expand_env.c \
			src/expander/heredoc_expander.c \
			src/expander/wildcard_expand.c \
			src/parse/checker/check_heredoc.c \
			src/parse/checker/checker_errors.c \
			src/parse/checker/checker.c \
			src/parse/Errors/Errors_1.c \
			src/parse/Errors/Errors_2.c \
			src/parse/heredoc/heredoc.c \
			src/parse/heredoc/input.c \
			src/parse/history/history.c \
			src/parse/lexer/ft_remove_quotes.c \
			src/parse/lexer/tokenizer.c \
			src/parse/lexer/retokenizer.c \
			src/parse/Multiple_Tools/cleanup.c \
			src/parse/Multiple_Tools/utils.c \
			src/parse/tree/ast_tree.c \
			src/parse/tree/ft_free_list.c \
			src/parse/tree/ft_free_redirections.c \
			src/parse/tree/ft_free_tree.c \
			src/parse/wildcards/wildcards.c \
			src/parse/wildcards/wildcards_utils.c \
			src/parse/wildcards/wildcards_files.c \
			src/parse/wildcards/ft_wdc_len.c \
			src/init.c \
			src/minishell.c \
			src/prompt.c \
			src/signals.c 

OBJ_DIR  = objects


OBJ = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

LIBFT = ./Libft/libft.a

all: $(NAME)
	@echo "			  $(GREEN) ███$(RED)╗$(GREEN)   ███$(RED)╗$(GREEN) ██$(RED)╗$(GREEN) ███$(RED)╗$(GREEN)   ██$(RED)╗$(GREEN) ██$(RED)╗$(GREEN) ███████$(RED)╗$(GREEN) ██$(RED)╗$(GREEN)  ██$(RED)╗$(GREEN) ███████$(RED)╗$(GREEN) ██$(RED)╗$(GREEN)      ██$(RED)╗$(GREEN)     $(NC)"
	@echo "			  $(GREEN) ████$(RED)╗$(GREEN) ████$(RED)║$(GREEN) ██$(RED)║$(GREEN) ████$(RED)╗$(GREEN)  ██$(RED)║$(GREEN) ██$(RED)║$(GREEN) ██$(RED)╔════╝$(GREEN) ██$(RED)║$(GREEN)  ██$(RED)║$(GREEN) ██$(RED)╔════╝$(GREEN) ██$(RED)║$(GREEN)      ██$(RED)║$(GREEN)     $(NC)"
	@echo "			  $(GREEN) ██$(RED)╔$(GREEN)████$(RED)╔$(GREEN)██$(RED)║$(GREEN) ██$(RED)║$(GREEN) ██$(RED)╔$(GREEN)██$(RED)╗$(GREEN) ██$(RED)║$(GREEN) ██$(RED)║$(GREEN) ███████$(RED)╗$(GREEN) ███████$(RED)║$(GREEN) █████$(RED)╗$(GREEN)   ██$(RED)║$(GREEN)      ██$(RED)║$(GREEN)     $(NC)"
	@echo "			  $(GREEN) ██$(RED)║$(GREEN)$(RED)╚$(GREEN)██$(RED)╔╝$(GREEN)██$(RED)║$(GREEN) ██$(RED)║$(GREEN) ██$(RED)║╚$(GREEN)██$(RED)╗$(GREEN)██$(RED)║$(GREEN) ██$(RED)║ ╚════$(GREEN)██$(RED)║$(GREEN) ██$(RED)╔══$(GREEN)██$(RED)║$(GREEN) ██$(RED)╔══╝$(GREEN)   ██$(RED)║$(GREEN)      ██$(RED)║$(GREEN)     $(NC)"
	@echo "			  $(GREEN) ██$(RED)║$(GREEN) $(RED)╚═╝$(GREEN) ██$(RED)║$(GREEN) ██$(RED)║$(GREEN) ██$(RED)║$(GREEN) $(RED)╚$(GREEN)████$(RED)║$(GREEN) ██$(RED)║$(GREEN) ███████$(RED)║$(GREEN) ██$(RED)║$(GREEN)  ██$(RED)║$(GREEN) ███████$(RED)╗$(GREEN) ███████$(RED)╗$(GREEN) ███████$(RED)╗$(GREEN)$(NC)"
	@echo "			  $(GREEN) $(RED)╚═╝$(GREEN)     $(RED)╚═╝$(GREEN) $(RED)╚═╝$(GREEN) $(RED)╚═╝$(GREEN)  $(RED)╚═══╝$(GREEN) $(RED)╚═╝$(GREEN) $(RED)╚══════╝$(GREEN) $(RED)╚═╝$(GREEN)  $(RED)╚═╝$(GREEN) $(RED)╚══════╝$(GREEN) $(RED)╚══════╝$(GREEN) $(RED)╚══════╝$(GREEN)$(NC)"
	@echo "						    $(GREEN)dgomez-l $(YELLOW)/ $(RED)ismherna$(NC)"
	@echo "						 NEVER GONNA GIVE YOU PIPE"


$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ) includes/minishell.h
	@echo "$(YELLOW)------------------------------------------------- Compiling Minishell ----------------------------------------------------$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(GREEN)------------------------------------------------ Minishell Finished Compiling --------------------------------------------$(NC)\n"
	@echo "$(GREEN)--------------------------------------------------------------------------------------------------------------------------$(NC)"
	@echo "$(GREEN)--------------------------------------------------- Minishell Is Ready ---------------------------------------------------$(NC)"
	@echo "$(GREEN)--------------------------------------------------------------------------------------------------------------------------$(NC)\n"

$(LIBFT):
	@make -sC ./Libft CFLAGS="$(CFLAGS)"

$(OBJ_DIR):
	@echo "$(RED)------------------------------------------- Object Directory Does Not Exist ----------------------------------------------$(NC)"
	@echo "$(YELLOW)----------------------------------------------- Creating Object Directory ------------------------------------------------$(NC)"
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)------------------------------------------------- Object Directory Done --------------------------------------------------$(NC)"

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)  # Esto garantiza que el directorio exista
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
	@printf "%-200s\r" ">Minishell compiling: ""$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<"

clean:
	@make -sC ./Libft fclean
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)--------------------------------------------------- Objects Cleaned ------------------------------------------------------$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)--------------------------------------------------- Minishell Cleaned ----------------------------------------------------$(NC)"

re: fclean all

.DEFAULT_GOAL: all

.PHONY: all clean fclean re
