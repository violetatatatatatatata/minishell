#include "../Includes/libft.h"

int	ft_isascii(int c)
{
	if ((sizeof(c) == sizeof(unsigned char)) || (c >= 0 && c <= 127))
	{
		return (1);
	}
	return (0);
}
