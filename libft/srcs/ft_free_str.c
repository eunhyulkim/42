#include "libft.h"

int		ft_free_str(char **str)
{
	if (!str || !(*str))
		return (0);
	free(*str);
	*str = 0;
	return (1);
}
