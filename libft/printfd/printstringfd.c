#include "ft_printfd.h"

int	printstringfd(int fd, char const *s)
{
	int	res;

	res = 0;
	if (s == NULL)
	{
		res += printstringfd(fd, "(null)");
		return (res);
	}
	while (*s != 0)
	{
		res += printcharfd(fd, *s);
		s++;
	}
	return (res);
}
