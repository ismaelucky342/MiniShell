GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m

NAME = minishell

SRC		=	src/env/env_hash.c \
			src/ast_tree/ast_process.c	\
			src/ast_tree/fill_ast_and_checks.c	\
			src/ast_tree/ft_ast_built.c	\
			src/ast_tree/ft_node_delete.c	\
			src/ast_tree/ft_node_new.c	\
			src/ast_tree/ft_tree_build_err.c \
			src/env/print_env.c \
			src/Tokens_utils/ascii_dictionary.c \
			src/Tokens_utils/ft_token_copy.c \
			src/Tokens_utils/ft_token_del.c \
			src/Tokens_utils/ft_token_list_del.c \
			src/Tokens_utils/ft_token_new.c \
			src/Tokens_utils/ft_token_parenthesis.c \
			src/Tokens_utils/ft_token_type.c	\
			src/Tokens_utils/Tokenizer/ft_tokenizer_refill_line.c	\
			src/Tokens_utils/Tokenizer/tokenizer_actions.c	\
			src/Tokens_utils/Tokenizer/tokenizer_delete.c	\
			src/Tokens_utils/Tokenizer/tokenizer_errors.c	\
			src/Tokens_utils/Tokenizer/tokenizer_new.c	\
			src/Tokens_utils/Tokenizer/tokenizer_type.c	\
			src/Tokens_utils/Tokenizer/tokenizer.c \
			src/minishell.c

OBJ_DIR  = objects

OBJ = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize="address"

LIBFT = ./Libft/libft.a

all: $(NAME)
	@echo "$(GREEN) ███$(RED)╗$(GREEN)   ███$(RED)╗$(GREEN) ██$(RED)╗$(GREEN) ███$(RED)╗$(GREEN)   ██$(RED)╗$(GREEN) ██$(RED)╗$(GREEN) ███████$(RED)╗$(GREEN) ██$(RED)╗$(GREEN)  ██$(RED)╗$(GREEN) ███████$(RED)╗$(GREEN) ██$(RED)╗$(GREEN)      ██$(RED)╗$(GREEN)     $(NC)"
	@echo "$(GREEN) ████$(RED)╗$(GREEN) ████$(RED)║$(GREEN) ██$(RED)║$(GREEN) ████$(RED)╗$(GREEN)  ██$(RED)║$(GREEN) ██$(RED)║$(GREEN) ██$(RED)╔════╝$(GREEN) ██$(RED)║$(GREEN)  ██$(RED)║$(GREEN) ██$(RED)╔════╝$(GREEN) ██$(RED)║$(GREEN)      ██$(RED)║$(GREEN)     $(NC)"
	@echo "$(GREEN) ██$(RED)╔$(GREEN)████$(RED)╔$(GREEN)██$(RED)║$(GREEN) ██$(RED)║$(GREEN) ██$(RED)╔$(GREEN)██$(RED)╗$(GREEN) ██$(RED)║$(GREEN) ██$(RED)║$(GREEN) ███████$(RED)╗$(GREEN) ███████$(RED)║$(GREEN) █████$(RED)╗$(GREEN)   ██$(RED)║$(GREEN)      ██$(RED)║$(GREEN)     $(NC)"
	@echo "$(GREEN) ██$(RED)║$(GREEN)$(RED)╚$(GREEN)██$(RED)╔╝$(GREEN)██$(RED)║$(GREEN) ██$(RED)║$(GREEN) ██$(RED)║╚$(GREEN)██$(RED)╗$(GREEN)██$(RED)║$(GREEN) ██$(RED)║ ╚════$(GREEN)██$(RED)║$(GREEN) ██$(RED)╔══$(GREEN)██$(RED)║$(GREEN) ██$(RED)╔══╝$(GREEN)   ██$(RED)║$(GREEN)      ██$(RED)║$(GREEN)     $(NC)"
	@echo "$(GREEN) ██$(RED)║$(GREEN) $(RED)╚═╝$(GREEN) ██$(RED)║$(GREEN) ██$(RED)║$(GREEN) ██$(RED)║$(GREEN) $(RED)╚$(GREEN)████$(RED)║$(GREEN) ██$(RED)║$(GREEN) ███████$(RED)║$(GREEN) ██$(RED)║$(GREEN)  ██$(RED)║$(GREEN) ███████$(RED)╗$(GREEN) ███████$(RED)╗$(GREEN) ███████$(RED)╗$(GREEN)$(NC)"
	@echo "$(GREEN) $(RED)╚═╝$(GREEN)     $(RED)╚═╝$(GREEN) $(RED)╚═╝$(GREEN) $(RED)╚═╝$(GREEN)  $(RED)╚═══╝$(GREEN) $(RED)╚═╝$(GREEN) $(RED)╚══════╝$(GREEN) $(RED)╚═╝$(GREEN)  $(RED)╚═╝$(GREEN) $(RED)╚══════╝$(GREEN) $(RED)╚══════╝$(GREEN) $(RED)╚══════╝$(GREEN)$(NC)"
	@echo "			   $(GREEN)dgomez-l $(NC)/ $(RED)ismherna$(NC)"
	@echo "			NEVER GONNA GIVE YOU PIPE"


$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ) includes/minishell.h
	@echo "$(YELLOW)--------------------- Compiling Minishell ----------------------$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)------------------ Minishell Finished Compiling ----------------$(NC)\n"
	@echo "$(GREEN)----------------------------------------------------------------$(NC)"
	@echo "$(GREEN)---------------------- Minishell Is Ready ----------------------$(NC)"
	@echo "$(GREEN)----------------------------------------------------------------$(NC)\n"

$(LIBFT):
	@make -sC ./Libft

$(OBJ_DIR):
	@echo "$(RED)--------------- Object Directory Does Not Exist ----------------$(NC)"
	@echo "$(YELLOW)------------------ Creating Object Directory -------------------$(NC)"
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/src/env
	@mkdir -p $(OBJ_DIR)/src/ast_tree
	@mkdir -p $(OBJ_DIR)/src/Tokens_utils
	@mkdir -p $(OBJ_DIR)/src/Tokens_utils/Tokenizer
	@echo "$(GREEN)-------------------- Object Directory Done ---------------------$(NC)"

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)  # Esto garantiza que el directorio exista
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
	@printf "%-100s\r" ">Minishell compiling: ""$(CC) -o $@"

clean:
	@make -sC ./Libft fclean
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)----------------------- Objects Cleaned ------------------------$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)---------------------- Minishell Cleaned -----------------------$(NC)"

re: fclean all

.DEFAULT_GOAL: all

.PHONY: all clean fclean re

