#include "../Includes/libft.h"

int	ft_tolower(int str)
{
	if (str < 91 && str > 64)
	{
		str = str + 32;
	}
	return (str);
}
