#include "../Includes/libft.h"

int	ft_isalpha(int c)
{
	if (c < 65 || c > 122 || (c < 97 && c > 90))
	{
		return (0);
	}
	return (1);
}
