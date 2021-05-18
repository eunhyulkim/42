#include "convert.hpp"

namespace convert {
	void	main(std::string arg)
	{
		Converter machine;
		machine.parse(arg);
		machine.convert();
		machine.print();
	}
}

int		main(int ac, char *av[])
{
	if (ac != 2)
	{
		std::cerr << "There must be two arguments." << std::endl;
		return (0);
	}
	convert::main(av[1]);
	return (0);
}
