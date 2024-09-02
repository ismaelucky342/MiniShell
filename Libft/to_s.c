
#include "libft.h"

int			to_s(char *buf, int *dir, va_list ap)
{
	char	*str;
	char	*s;
	char	fill;
	int		len;
	int		i;

	s = va_arg(ap, char *);
	s == NULL ? s = NULLSTR : 0;
	len = ft_strnlen(s, dir[PF_PREC]);
	fill = ' ';
	if (dir[PF_ZERO] == 1)
		fill = '0';
	str = buf;
	i = -1;
	if (dir[PF_LEFT] != 1)
		while (len < dir[PF_WIDTH]--)
			*str++ = fill;
	while (++i < len)
		*str++ = *s++;
	while (len < dir[PF_WIDTH]--)
		*str++ = ' ';
	return (str - buf);
}
