#include "eval_expr.hpp"

namespace {
	void	ft_error(char const *msg){
		std::cout << msg << std::endl;
		exit(EXIT_FAILURE);
	}
}
int		main(int ac, char *av[])
{
	if (ac != 2)
	{
		ft_error("expr is not exist.");
		return (EXIT_SUCCESS);
	}
	try {
		parse::main(av[1]);
	} catch (char const *msg) {
		ft_error(msg);
	}
	std::cout << "PARSE IS SUCCESS" << std::endl;
}