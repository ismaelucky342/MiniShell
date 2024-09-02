

#include "libft.h"

int		skip_atoi(const char **s)
{
	int	nb;

	nb = 0;
	while (**s >= '0' && **s <= '9')
		nb = nb * 10 + *((*s)++) - '0';
	return (nb);
}
