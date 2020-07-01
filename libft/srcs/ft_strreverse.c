#include "libft.h"

char	*ft_strreverse(char *src)
{
	char	*str;
	int		idx;
	int		len;

	if (!src || !(*src))
		return (0);
	len = ft_strlen(src);
	str = (char *)ft_calloc(sizeof(char), len + 1);
	idx = 0;
	while (idx < len)
	{
		str[idx] = src[len - idx - 1];
		idx++;
	}
	return (str);
}
