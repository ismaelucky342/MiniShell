GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m

NAME = minishell

SRC_DIR =	src
SRC		=	env/env_hash.c\
			env/print_env.c\
			parsing/ft_free_tree.c\
			parsing/ft_free_tree_val.c\
			parsing/ft_free_tree_node.c\
			parsing/ft_create_tree_node.c \
			parsing/ft_malloc_node.c \
			parsing/ft_free_rlist.c\
			parsing/ft_init_rnode.c \
			parsing/ft_add_rnode.c \
			parsing/parser.c \
			signals/signals.c\
			main/minishell.c \

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
	@mkdir $(OBJ_DIR)/env
	@mkdir $(OBJ_DIR)/parsing
	@mkdir $(OBJ_DIR)/signals
	@mkdir $(OBJ_DIR)/main

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

.PHONY: all clean fclean re
