#include "libft.h"

void		*ft_new_node(
	size_t size, void (*f)(void *, int, va_list), int nb_arg, ...)
{
	va_list	ap;
	void	*new;

	new = mmalloc(size);
	va_start(ap, nb_arg);
	f(new, nb_arg, ap);
	va_end(ap);
	return (new);
}
