
#include "libft.h"

int	to_c(char *buf, int *dir, va_list ap)
{
	char	*str;
	char	fill;
	int		spec_char;

	str = buf;
	fill = ' ';
	dir[PF_WIDTH]--;

	if (dir[PF_PREC] == -1 && dir[PF_ZERO] == 1)
		fill = '0';

	if (dir[PF_LEFT] != 1)
	{
		while (0 < dir[PF_WIDTH]--)
			*str++ = fill;
	}

	if (dir[PF_SPEC] == -1)
	{
		spec_char = '\0';
	}
	else
	{
		if (dir[PF_SPEC] == 8)
			spec_char = '%';
		else
			spec_char = va_arg(ap, int);
	}
	*str++ = spec_char;

	while (0 < dir[PF_WIDTH]--)
		*str++ = ' ';

	if (dir[PF_SPEC] == -1)
		return (str - buf - 1);
	else
		return (str - buf);
}
