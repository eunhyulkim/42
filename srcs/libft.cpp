#include "libft.hpp"

namespace ft
{
	std::string
	getStringFromFile(std::string file_path)
	{
		int fd = -1;
		int read_cnt = 0;
		char buff[1024];
		std::string ret;

		if ((fd = open(file_path.c_str(), O_RDONLY)) == -1)
			return (std::string(""));
		while ((read_cnt = read(fd, buff, 1024)) > 0)
			ret.append(buff, read_cnt);
		close(fd);
		return (ret);
	}
}
