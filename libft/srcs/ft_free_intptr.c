#include "libft.h"

int		ft_free_intptr(int **intptr)
{
	if (!intptr || !(*intptr))
		return (0);
	free(*intptr);
	*intptr = 0;
	return (1);
}
