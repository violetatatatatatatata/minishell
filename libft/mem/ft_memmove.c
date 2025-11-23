#include "../Includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t c)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!src && !dest)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest < src)
		ft_memcpy(dest, src, c);
	else
	{
		while (c--)
			d[c] = s[c];
	}
	return (dest);
}
