#include "../Includes/libft.h"

unsigned long	ft_strlen(const char *str)
{
	unsigned long	count;

	count = 0;
	while (*str)
	{
		count++;
		str++;
	}
	return (count);
}
