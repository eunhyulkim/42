#include "cat.hpp"

int		main(int ac, char *av[])
{
	if (ac == 1)
	{
		cat::from_stdin();
		return (0);
	}
	cat::from_files(ac, av);
	return (0);
}
