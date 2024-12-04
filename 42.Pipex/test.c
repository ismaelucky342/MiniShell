#include <stddef.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	long long			ll;
	long int			li;
	long				l;
	unsigned long		ul;
	size_t				st;

	int					i;
	short int			si;
	short				s;
	unsigned int		ui;
	unsigned short		us;
	unsigned short int	usi;

	printf("ll: %lu\nli: %lu\nl: %lu\nul: %lu\nst: %lu\n\n", sizeof(ll), sizeof(li), sizeof(l), sizeof(ul), sizeof(st));
	printf("i: %lu\nsi: %lu\ns: %lu\nui: %lu\nus: %lu\nusi: %lu\n", sizeof(i), sizeof(si), sizeof(s), sizeof(ui), sizeof(us), sizeof(usi));
	return (0);
}
