GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m

NAME = minishell

VPATH = src/env/:src/expander/:src/parse/checker/:src/parse/Errors/:src/parse/heredoc/:src/parse/history/:src/parse/lexer/:src/parse/Multiple_Tools/:src/parse/tree/:src/parse/wildcards/:src/

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


OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

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

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
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
