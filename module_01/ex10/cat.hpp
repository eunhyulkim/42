#ifndef CAT_HPP
# define CAT_HPP

#include <iostream>
#include <fstream>
#include <string>

namespace cat {
	void	from_stdin(void);
	void	from_files(int ac, char *av[]);
}
#endif
