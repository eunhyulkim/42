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
		return (ret);
	}

	std::vector<std::string>
	split(std::string s, char c)
	{
		std::vector<std::string> ret;
		size_t pos = 0;
		while ((pos = s.find(c)) != std::string::npos)
		{
			if (pos != 0)
				ret.push_back(s.substr(0, pos));
			s.erase(0, pos + 1);
		}
		if (s.length() != 0)
			ret.push_back(s);
		return (ret);
	}
}
