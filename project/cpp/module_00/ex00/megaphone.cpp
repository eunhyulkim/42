#include <iostream>

namespace {
	void	print_upperstr(char *av)
	{
		int		i;

		if (!av)
		{
			std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
			return ;
		}
		i = -1;
		while (av[++i])
			std::cout << static_cast<char>(toupper(av[i]));
	}
}

int		main(int ac, char *av[])
{
	int		i;

	i = 1;
	if (ac > 1)
	{
		while (i < ac)
			print_upperstr(av[i++]);
		std::cout << std::endl;
	}
	else
		print_upperstr(NULL);
	return (0);
}
