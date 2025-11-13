#include "ft_printf.h"

int	printstring(char const *s)
{
	int	res;

	res = 0;
	if (s == NULL)
	{
		res += printstring("(null)");
		return (res);
	}
	while (*s != 0)
	{
		res += printchar(*s);
		s++;
	}
	return (res);
}
