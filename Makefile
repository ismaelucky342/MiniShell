GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m

NAME = minishell
INCLUDEPATH = 

SRC_DIR =	src
SRC		=	env/env_hash.c\
			env/print_env.c\
			hashtable/ft_add_element.c\
			hashtable/ft_ch_value.c\
			hashtable/ft_create_element.c\
			hashtable/ft_create_hashtable.c\
			hashtable/ft_delete_element.c\
			hashtable/ft_free_hashtable.c\
			hashtable/ft_get_value.c\
			hashtable/ft_monkey_hash.c\
			hashtable/ft_print_hashtable.c\
			parsing/free_tree.c\
			parsing/ft_count_element.c\
			parsing/ft_create_tree_node.c\
			parsing/ft_is_redir.c\
			parsing/ft_malloc_node.c\
			parsing/ft_node_redirect.c\
			parsing/ft_rlist_cleanup.c\
			parsing/parser.c\
			signals/signals.c\

OBJ_DIR  = objects
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize="address"

LIBFT = ./Libft/libft.a

all: $(NAME)
	@echo "$(GREEN)----------------------------------------------------------------$(NC)"
	@echo "$(GREEN)---------------------- Minishell Is Ready ----------------------$(NC)"
	@echo "$(GREEN)----------------------------------------------------------------$(NC)"

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ) minishell.h
	@echo "$(YELLOW)--------------------- Compiling Minishell ----------------------$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -I $(INCLUDEPATH)
	@echo "$(GREEN)------------------ Minishell Finished Compiling ----------------$(NC)\n"

$(LIBFT):
	@make -sC ./Libft

$(OBJ_DIR):
	@echo "$(YELLOW)------------------ Creating Object Directory -------------------$(NC)"
	@mkdir $(OBJ_DIR)

%.o: ../$(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@make -sC ./Libft fclean
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)----------------------- Objects Cleaned ------------------------$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)---------------------- Minishell Cleaned -----------------------$(NC)"

re: fclean all

.PHONY: all clean fclean re
