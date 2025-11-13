#include "../Includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			iter;
	unsigned char	*s;
	unsigned char	*z;

	iter = 0;
	s = (unsigned char *)s1;
	z = (unsigned char *)s2;
	while (iter < n)
	{
		if (*s != *z)
		{
			return (*s - *z);
		}
		iter++;
		s++;
		z++;
	}
	return (0);
}
