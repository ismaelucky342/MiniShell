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
			src/tokens/ascii_dictionary.c \
			src/tokens/ft_token_copy.c \
			src/tokens/ft_token_del.c \
			src/tokens/ft_token_list_del.c \
			src/tokens/ft_token_new.c \
			src/tokens/ft_token_parenthesis.c \
			src/tokens/ft_token_type.c	\
			src/minishell.c		\

OBJ_DIR  = objects

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize="address"

LIBFT = ./Libft/libft.a

all: $(NAME)
	@echo "$(GREEN)----------------------------------------------------------------$(NC)"
	@echo "$(GREEN)---------------------- Minishell Is Ready ----------------------$(NC)"
	@echo "$(GREEN)----------------------------------------------------------------$(NC)"
	@echo ""
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
	@$(CC) $(CFLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ)) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)------------------ Minishell Finished Compiling ----------------$(NC)\n"

$(LIBFT):
	@make -sC ./Libft

$(OBJ_DIR):
	@echo "$(YELLOW)------------------ Creating Object Directory -------------------$(NC)"
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)/src
	@mkdir $(OBJ_DIR)/src/env
	@mkdir $(OBJ_DIR)/src/ast_tree
	@mkdir $(OBJ_DIR)/src/tokens

	@echo "$(GREEN)-------------------- Object Directory Done ---------------------$(NC)"

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $(addprefix $(OBJ_DIR)/, $@) $<

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
