GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m

NAME = minishell

SRC		=	src/execution/builtins/cd.c \
			src/execution/nodes/pipes.c \
			src/execution/utils/error.c \
			src/main/cleanup.c \
			src/main/minishell.c \
			src/main/signals/configure_terminal.c \
			src/main/signals/exec_handler.c \
			src/main/signals/parse_handler.c \
			src/main/signals/restore_terminal.c \
			src/parser/ast_tree/ast_utils/delete_parenthesis.c \
			src/parser/ast_tree/ast_utils/ft_ast_new_node.c \
			src/parser/ast_tree/ast_utils/ft_ast_new_redir_node.c \
			src/parser/ast_tree/ast_utils/ft_ast_node_delete.c \
			src/parser/ast_tree/heredoc/ast_walker.c \
			src/parser/ast_tree/heredoc/cmd_handle.c \
			src/parser/ast_tree/heredoc/ft_get_line.c \
			src/parser/ast_tree/heredoc/heredoc.c \
			src/parser/ast_tree/heredoc/redir_handle.c \
			src/parser/ast_tree/redirection.c \
			src/parser/ast_tree/tree_errors.c \
			src/parser/ast_tree/pipe_line.c \
			src/parser/checker/check_quotes.c \
			src/parser/checker/check_unclosed.c \
			src/parser/checker/check.c \
			src/parser/env/env_hash.c \
			src/parser/env/print_env.c \
			src/parser/parser.c \
			src/parser/prompt/prompt_colors.c \
			src/parser/prompt/prompt.c \
			src/parser/tokens/tokenizador.c \
			src/parser/tokens/t_utils.c \

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
	@mkdir $(OBJ_DIR)/src/execution
	@mkdir $(OBJ_DIR)/src/execution/builtins
	@mkdir $(OBJ_DIR)/src/execution/nodes
	@mkdir $(OBJ_DIR)/src/execution/utils
	@mkdir $(OBJ_DIR)/src/main
	@mkdir $(OBJ_DIR)/src/main/signals
	@mkdir $(OBJ_DIR)/src/parser
	@mkdir $(OBJ_DIR)/src/parser/ast_tree
	@mkdir $(OBJ_DIR)/src/parser/ast_tree/ast_utils
	@mkdir $(OBJ_DIR)/src/parser/ast_tree/heredoc
	@mkdir $(OBJ_DIR)/src/parser/checker
	@mkdir $(OBJ_DIR)/src/parser/env
	@mkdir $(OBJ_DIR)/src/parser/prompt
	@mkdir $(OBJ_DIR)/src/parser/tokens
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
