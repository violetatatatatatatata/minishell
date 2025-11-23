#include "../Includes/libft.h"

int	ft_toupper(int str)
{
	if (str < 123 && str > 96)
	{
		str = str - 32;
	}
	return (str);
}
