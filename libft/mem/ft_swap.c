#include "../Includes/libft.h"

void	ft_swap(int *a, int *b)
{
	int	ta;
	int	tb;

	ta = *a;
	tb = *b;
	*a = tb;
	*b = ta;
}
