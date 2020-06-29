#include <stdio.h>
#include "libft.h"

void	test_in(void)
{
	printf("%d\n", ft_in(0, "['DEF', 'GHI']"));
	printf("%d\n", ft_in("['DEF', 'GHI']", 0));
	printf("%d\n", ft_in(0, 0));
	printf("%d\n", ft_in("ABC", ""));
	printf("%d\n", ft_in("", ""));
	printf("%d\n", ft_in("", "['DEF', 'GHI']"));
	printf("%d\n", ft_in("ABC", "['DEF', 'ABC]"));
	printf("%d\n", ft_in("ABC", "['DEF', 'AB']"));
	printf("%d\n", ft_in("ABC", "['DEF', 'ABC']"));
	printf("%d\n", ft_in("ABC", "['DEF', 'ABC', 'FGH']"));
	printf("%d\n", ft_in("ABC", "['DEF', 'ABCDE']"));
}

void	test_isitem(void)
{
	char	**str;
	str = (char **)ft_calloc(sizeof(char *), 4);
	str[0] = ft_strdup("ABC");
	str[1] = ft_strdup("DEF");
	str[2] = ft_strdup("GHI");
	printf("%d\n", ft_isitem("DEF", str));
	printf("%d\n", ft_isitem("AB", str));
	printf("%d\n", ft_isitem("GHI", str));
	ft_free_doublestr(str);
}

int main(void)
{
	return (0);
}
