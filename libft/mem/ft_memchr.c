#include "../Includes/libft.h"

void	*ft_memchr(const void *s, int c, unsigned long n)
{
	unsigned long	iter;
	void			*ns;

	ns = (void *)s;
	iter = 0;
	while (iter < n)
	{
		if (((unsigned char *)ns)[iter] == (unsigned char)c)
		{
			return (ns + iter);
		}
		iter++;
	}
	return (NULL);
}
