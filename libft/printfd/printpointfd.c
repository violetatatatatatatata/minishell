#include "ft_printfd.h"

int	printpointcontfd(int fd, unsigned long long n, char *base)
{
	unsigned long long	num;
	int					res;

	res = 0;
	num = (unsigned long long)n;
	if (num > 16)
	{
		res += printpointcontfd(fd, (num / 16), base);
		res += printpointcontfd(fd, num % 16, base);
	}
	else if (num == 16)
	{
		res += printstringfd(fd, "10");
	}
	else
	{
		printcharfd(fd, base[num]);
		res++;
	}
	return (res);
}

int	printpointfd(int fd, unsigned long long n, char *base)
{
	int	res;

	res = 0;
	if (n == 0)
	{
		res += printstringfd(fd, "(nil)");
		return (res);
	}
	res += printstringfd(fd, "0x");
	res += printpointcontfd(fd, n, base);
	return (res);
}
