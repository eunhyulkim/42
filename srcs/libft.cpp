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
			throw (std::invalid_argument("Failed open to " + file_path));
		while ((read_cnt = read(fd, buff, 1024)) > 0)
			ret.append(buff, read_cnt);
		close(fd);
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
			if (stringVector[i].find(sep) == 0)
				throw (std::invalid_argument("Not found key in string"));
			std::string data = trim(stringVector[i], " \t");
			std::string key = data.substr(0, data.find(sep));
			std::string value;
			if (stringVector[i].find(sep) < stringVector[i].size() - 1)
				value = data.substr(key.size() + 1);
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
