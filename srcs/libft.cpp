#include "libft.hpp"

namespace ft
{
	std::string
	ltrim(std::string s, std::string seps)
	{
		std::string ret;
		int size = s.size();
		int idx = 0;

		if (size == 0)
			return (ret);
		while (idx < size && seps.find(s[idx]) != std::string::npos)
			++idx;
		if (idx == size)
			return (ret);
		return (s.substr(idx));
	}

	std::string
	rtrim(std::string s, std::string seps)
	{
		std::string ret;
		int size = s.size();
		int idx = size - 1;

		if (size == 0)
			return (ret);
		while (idx >= 0 && seps.find(s[idx]) != std::string::npos)
			--idx;
		if (idx == -1)
			return (ret);
		return (s.substr(0, idx + 1));
	}

	std::string
	trim(std::string s, std::string seps) {
		return (rtrim(ltrim(s, seps), seps));
	}

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

	std::set<std::string>
	stringVectorToSet(std::vector<std::string> stringVector)
	{
		std::set<std::string> ret;

		for (int i = 0; i < stringVector.size(); ++i) {
			ret.insert(stringVector[i]);
		}
		return (ret);
	}

	std::map<std::string, std::string>
	stringVectorToMap(std::vector<std::string> stringVector, char sep)
	{
		std::map<std::string, std::string> ret;

		if (stringVector.size() == 0)
			return ret;
		for (int i = 0; i < stringVector.size(); ++i)
		{
			if (stringVector[i].find(sep) == std::string::npos)
				throw (std::invalid_argument("Not found sep in string"));
			std::string key = stringVector[i].substr(0, stringVector[i].find(sep));
			std::string value = stringVector[i].substr(key.size() + 1);
			ret.insert(std::pair<std::string, std::string>(trim(key, " \t"), trim(value, " \t")));
		}
		return (ret);
	}

	std::string
	setToString(std::set<std::string> string_set, std::string sep)
	{
		std::string ret;
		for (std::set<std::string>::iterator it = string_set.begin(); it != string_set.end(); ++it)
		{
			ret.append(*it);
			if (++it != string_set.end())
				ret.append(sep);
			--it;
		}
		return (ret);
	}
}
