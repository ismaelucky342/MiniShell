/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:20:17 by ismherna          #+#    #+#             */
/*   Updated: 2024/09/06 14:20:17 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define DLL_SUCCESS 0
# define DLL_FAILURE 1

/*-----------FT_PRINTF DEFINES----------------------*/

# define PF_BUFF_SIZE 16384
# define C_SPEC "cspdiuxX%n"
# define NULLSTR "(null)"

/*-----------GET NEXT LINE DEFINES----------------------*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif
/*--------------PRINTF STRUCTS--------------------------*/

typedef enum e_ft_printf_dir
{
	PF_ZERO,
	PF_LEFT,
	PF_PLUS,
	PF_SPACE,
	PF_SMALL,
	PF_S,
	PF_LONG,
	PF_SHORT,
	PF_WIDTH,
	PF_PREC,
	PF_SPEC
}	t_ft_printf_dir;

/*--------------LIST ------------------------*/

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

/*--------------MMALLOC ------------------------*/

typedef struct s_mem_context
{
	t_list	*allocated_list;
}	t_mem_context;


/*-------------DOUBLE LINKED LIST--------------------------*/

typedef struct s_pattern_list_np
{
	struct s_pattern_list_np	*next;
	struct s_pattern_list_np	*prev;
}	t_pattern_list_np;

typedef struct s_pattern_list_np	t_pnp;

/*------------------BOOLEAN--------------------------------*/
/*
typedef int		t_bool;
# define TRUE 1
# define FALSE 0
*/
/*--------------STRUCT HASH --------------------------*/
typedef struct s_element
{
	char				*key;
	char				*value;
	struct s_element	*next;
}	t_element;

typedef struct s_hashtable
{
	t_element		**element_array;
	int				length;
}	t_hashtable;

// new functions
void		ft_bin2ascii(char *s);
char		*ft_string2bin(char *s, size_t i, size_t j);
void		ft_char2bin(unsigned char c, char *ret, size_t *j);
char		*ft_add_fs(char *start, char c);
int			ft_ishexdigit(int c);
int			ft_isspace(int c);
void		free_2d(char **arr);
int64_t		ft_atoll(const char *str);
int			ft_sqrt(int number);
int			checkd_bf(int *numbers, int count);
void		ins_sort(int array[], int n);

/*---------------PRINTF--------------------------------*/
// dprintf update
void		ft_specifier(int *dir, const char **format, int i, va_list ap);
void		handle_format_flags(int *dir, const char **f);
void		process_width_precision(int *dir, const char **f, va_list ap);
void		ft_initdir(int *dir, const char **f, va_list ap);
int			ft_printf(const char *format, ...);
int			ft_printf_fd(int fd, const char *format, ...);
int			ft_strnlen(char *str, int n);
int			skip_atoi(const char **s);
int			to_c(char *buf, int *dir, va_list ap);
int			to_s(char *buf, int *dir, va_list ap);
int			to_nbr(char *buf, int *dir, va_list ap);
void		ft_itoa_b(char *addr, unsigned long long nbr, int *dir);
char		*fill_width(char *str, int *dir, char fill_char);
char		*ft_number_str(char *n, char *str, char sign, int *dir);
char		*ft_number_str(char *n, char *str, char sign, int *dir);
long long	get_nbr(int *dir, va_list ap);
void		to_n(int i, int *dir, va_list ap);
int			ft_printf_fd(int fd, const char *format, ...);
//simple printf
int			ft_print_char(int character);
int			ft_printf(const char *str, ...);
int			ft_print_str(char *str);
int			ft_print_number(int n);
int			ft_print_unsigned(unsigned int n);
int			ft_print_hex(unsigned int num, const char word);
int			ft_print_pointer(unsigned long long ptr);

// libft
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strjoin_free(char *s1, const char *s2);
void		ft_close(int fd);
void		skip_spaces(char *str, int *i, int *start, int mode);
char		ft_is_reserved_char(char c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *str);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *dst, const void *str, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_mstrdup( char *s1);
char		*ft_strsub( char const *s, unsigned int start,
				size_t len);
char		*ft_strncpy(char *s1, const char *s2, size_t n);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		**ft_split(char const *s, char c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_mstrtrim( char const *s1, char const *set);
char		*ft_itoa(int n);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_msubstr( char const *s, unsigned int start, size_t len);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_print_error(char *title, int code, char *line);
t_list		*ft_lstnew(void *data);
void		ft_lstadd_front(t_list **list, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *list, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*---------------------HASH FUNCTIONS------------------------------------*/

t_hashtable	*ft_add_element( t_hashtable *ht, char *key, char *value);
t_element	*ft_get_element(t_hashtable *ht, char *key);
t_hashtable	*ft_ch_value(t_hashtable *ht, char *key, char *value, int is_apnd);
t_element	*ft_create_element( char *key, char *value);
t_hashtable	*ft_create_hashtable(int length);
int			ft_delete_element(t_hashtable *ht, char *key);
void		ft_free_hashtable(t_hashtable *hashtable);
void		ft_free_element(t_element *element);
char		*ft_get_value(t_hashtable *hashtable, char *key);
int			ft_monkey_hash(const char *str, int length);
void		ft_print_hashtable(t_hashtable *hashtable, char *delimeter);
int			ft_arraylen(char **str);
int			ft_next_prime(int nbr);
int			ft_index(char *str, char c);
int			ft_is_prime(int nbr);

/*------------------DOUBLE LINKED LIST FILES------------------------------*/
void		ft_del_list_np(t_pnp **lst);
void		*ft_new_node(size_t size,
				void (*f)(void *, int, va_list), int nb_arg, ...);
void		ft_add_node_end_np(t_pnp **lst, t_pnp *new);
void		ft_add_node_f_nextto_np(t_pnp **lst, t_pnp *new,
				int (*f)(t_pnp *curr));
void		ft_add_node_f_prevto_np(t_pnp **lst, t_pnp *new,
				int (*f)(t_pnp *curr));
void		ft_add_node_nextto_np(t_pnp *prev, t_pnp *new);
void		ft_add_node_prevto_np(t_pnp **start, t_pnp *next, t_pnp *new);
void		ft_add_node_start_np(t_pnp **lst, t_pnp *new);
void		ft_del_node_end_np(t_pnp **lst, void (*f)(t_pnp *curr));
void		ft_del_node_np(t_pnp **lst, t_pnp *del, void (*f)(t_pnp *curr));
void		ft_del_node_start_np(t_pnp **lst, void (*f)(t_pnp *curr));
void		ft_foreach_node_f_np(t_pnp **lst, int (*f)(t_pnp *curr));
void		ft_swap_node_np(t_pnp **lst, t_pnp *node_a, t_pnp *node_b);

/*---------------------GET NEXT LINE ------------------------------------*/
//char	*get_next_line(int fd); V1
char		*get_next_line_bonus(int fd);
char		*get_next_line(int fd);
char		*ft_strdup_gnl(char *s);
size_t		ft_strlen_gnl(char *s);
char		*ft_substr_gnl(char *s, unsigned int start, size_t len);
char		*ft_strjoin_gnl(char *s1, char *s2);
void		fill_str_gnl(char *res, char *s1, char *s2);

#endif