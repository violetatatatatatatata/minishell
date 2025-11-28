#include "../Includes/libft.h"

unsigned long	ft_strlen(const char *str)
{
	char	*s;

	s = (char *)str;
	while (*s)
		s++;
	return (s - str);
}
