GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m

NAME = minishell

SRC_DIR =	src
SRC		=	test.c\

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
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)------------------ Minishell Finished Compiling ----------------$(NC)\n"

$(LIBFT):
	@make -sC ./Libft bonus

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
