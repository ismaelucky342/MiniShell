GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m

SRC =	checkD_bf.c \
		free_2d.c \
		ft_addFS.c \
		ft_add_element.c \
		ft_arraylen.c \
		ft_atoi.c \
		ft_atoll.c \
		ft_bin2ascii.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_ch_value.c \
		ft_char.c \
		ft_char2bin.c \
		ft_create_element.c \
		ft_create_hashtable.c \
		ft_delete_element.c \
		ft_free_hashtable.c \
		ft_get_value.c \
		ft_hexadecimals.c \
		ft_index.c \
		ft_is_prime.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_ishexdigit.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_monkey_hash.c \
		ft_next_prime.c \
		ft_number.c \
		ft_pointers.c \
		ft_print_hashtable.c \
		ft_printf.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_sqrt.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_string.c \
		ft_string2bin.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_unsigned.c \
		ins_sort.c \
		ft_del_list_np.c \
		ft_new_node.c \
		ft_add_node_end_np.c \
		ft_add_node_f_nextto_np.c  \
		ft_add_node_f_prevto_np.c  \
		ft_add_node_nextto_np.c \
		ft_add_node_prevto_np.c \
		ft_add_node_start_np.c \
		ft_del_node_end_np.c \
		ft_del_node_np.c \
		ft_del_node_start_np.c \
		ft_foreach_node_f_np.c \
		ft_swap_node_np.c \
		mmalloc.c	\
		ft_printf_fd.c \
		ft_strnlen.c \
		skip_atoi.c \
		to_c.c \
		to_s.c \
		to_nbr.c \
		to_n.c \
		get_next_line_v1.c \
		get_next_line_v2.c \
		get_next_line_utils.c \
		get_next_line_bonus.c \
		ft_strncpy.c 	\
		ft_strsub.c
		
NAME = libft.a

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize="address"

all: speak $(NAME)
	@echo "$(GREEN)----------------------------------------------------------------$(NC)"
	@echo "$(GREEN)------------------------ Libft Is Ready ------------------------$(NC)"
	@echo "$(GREEN)----------------------------------------------------------------$(NC)\n"

$(NAME): $(OBJ) libft.h
	@ar -rcs $(NAME) $(OBJ)
	@echo "$(GREEN)------------------ Libft.a Finished Compiling ------------------$(NC)\n"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

speak:
	@echo "$(YELLOW)----------------------- Compiling Libft ------------------------$(NC)"

clean:
	@rm -f $(OBJ) $(B_OBJ)
	@echo "$(RED)------------------------ Libft Cleaned -------------------------$(NC)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all speak clean fclean re
