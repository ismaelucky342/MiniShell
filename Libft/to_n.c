#include "libft.h"

void	to_n(int printed, int *dir, va_list ap)
{
	int	*ptr;

	if (dir[PF_LONG] >= 0)
	{
		if (dir[PF_LONG] == 0)
			ptr = (int *)va_arg(ap, long *);
		else
			ptr = (int *)va_arg(ap, long long *);
	}
	else if (dir[PF_SHORT] >= 0)
	{
		if (dir[PF_SHORT] == 0)
			ptr = (int *)va_arg(ap, short int *);
		else
			ptr = (int *)va_arg(ap, signed char *);
	}
	else
		ptr = va_arg(ap, int *);
	*ptr = printed;
}
