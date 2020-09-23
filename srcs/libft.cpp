#include "libft.hpp"

namespace ft
{
	void
	bzero(void *data, size_t len)
	{
		unsigned char *str;

		str = (unsigned char *)data;
		while (len > 0)
			str[--len] = 0;
	}

	void *
	memcpy(void *dest, const void *src, size_t len)
	{
		char *d = reinterpret_cast<char *>(dest);
		const char *s = reinterpret_cast<const char *>(src);
		while (len--)
			*d++ = *s++;
		return dest;
	}

	void
	*calloc(size_t size, size_t count)
	{
		void		*addr;

		if (!(addr = malloc(size * count)))
			return (0);
		memset(addr, 0, size * count);
		return (addr);
	}

	char *
	strdup(const char *s)
	{
		size_t len = strlen(s) + 1;
		void *str = malloc(len);
		if (str == NULL)
			return NULL;
		return (reinterpret_cast<char *>(ft::memcpy(str, s, len)));
	}

	int
	free(void *ptr)
	{
		if (ptr)
			free(ptr);
		return (1);
	}

	int
	freeStr(char **str)
	{
		if (!str || !(*str))
			return (0);
		free(*str);
		*str = 0;
		return (1);
	}

	int
	lenDoubleStr(char **str)
	{
		int		idx;

		idx = 0;
		if (!str || !(*str))
			return (0);
		while (*str++)
			idx++;
		return (idx);
	}

	char
	**dupDoubleStr(char **str)
	{
		char	**ret;
		int		len;

		len = lenDoublestr(str);
		if (!(ret = (char **)calloc(sizeof(char *), len + 1)))
			return (0);
		while (len--)
			if (!(ret[len] = strdup(str[len])))
				return (0);
		return (ret);
	}

	int
	freeDoublestr(char ***doublestr_addr)
	{
		int 	i;
		char	**doublestr;

		if (!doublestr_addr || !(*doublestr_addr))
			return (0);
		i = -1;
		doublestr = *doublestr_addr;
		while (doublestr[++i])
			ft::freeStr(&doublestr[i]);
		ft::free(doublestr);
		*doublestr_addr = 0;
		return (1);
	}

	char
	**reallocDoubleStr(char ***strs_ref, char *item)
	{
		char	**ret;
		char	**strs;
		int		len;

		strs = *strs_ref;
		if (!item)
			return (strs);
		len = lenDoublestr(strs) + 2;
		if (!(ret = (char **)calloc(sizeof(char *), len--)))
			return (0);
		ret[--len] = strdup(item);
		while (len--)
			if (!(ret[len] = strdup(strs[len])))
				return (0);
		*strs_ref = ret;
		freeDoublestr(&strs);
		return (ret);
	}

	char
	*strchr(const char *s, int c)
	{
		int		i;

		i = 0;
		while (s[i] != '\0')
		{
			if (s[i] == (char)c)
				return ((char *)s + i);
			i++;
		}
		if (s[i] == (char)c)
			return ((char *)s + i);
		return (0);
	}

	char
	*strsub(char const *s, unsigned int start, size_t len)
	{
		char	*str;
		size_t	i;

		if (!s)
			return (0);
		if (!(str = (char *)calloc(sizeof(char), len + 1)))
			return (0);
		i = 0;
		while (i < len)
		{
			str[i] = s[start + i];
			i++;
		}
		str[i] = '\0';
		return (str);
	}

	int
	startswith(const char *str, const char *sub)
	{
		int		i;

		i = 0;
		while (sub[i] != '\0' && str[i] == sub[i])
			i++;
		return (sub[i] == '\0');
	}

	namespace {
		char *strAdd(char *dst, char *src)
		{
			int		i;
			int		j;

			if (!src)
				return (dst);
			if (!dst)
				return (src);
			i = ft::strlen(dst);
			j = 0;
			while (src[j])
				dst[i++] = src[j++];
			return (dst);
		}
	}

	char
	*strsjoin(char *s1, char *s2, char *s3, char *s4)
	{
		char	*str;
		int		lens;

		lens = ft::strlen(s1) + ft::strlen(s2) + ft::strlen(s3) + ft::strlen(s4);
		if (!(str = (char *)calloc(sizeof(char), lens + 1)))
			return (0);
		strAdd(str, s1);
		strAdd(str, s2);
		strAdd(str, s3);
		strAdd(str, s4);
		return ((char *)str);
	}

	size_t
	pow(size_t root, size_t square) {
		size_t idx = 0;
		size_t ret = 1;
		while (idx++ < square) {
			ret *= root;
		}
		return (ret);
	}

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
	getStringFromFile(std::string file_path, size_t max_size)
	{
		int fd = -1;
		size_t read_cnt = 0;
		char buff[1024];
		std::string ret;

		if ((fd = open(file_path.c_str(), O_RDONLY)) == -1)
			throw (std::invalid_argument("Failed open to " + file_path));
		while ((read_cnt = read(fd, buff, 1024)) > 0) {
			ret.append(buff, read_cnt);
			if (max_size != -1 && ret.size() > max_size)
				throw (std::overflow_error("overflow max_size in getStringFromFile"));
		}
		close(fd);
		return (ret);
	}

	std::string
	getStringFromFd(int fd, size_t max_size)
	{
		int read_cnt = 0;
		char buff[1024];
		std::string ret;

		while ((read_cnt = read(fd, buff, 1024)) > 0) {
			ret.append(buff, read_cnt);
			if (max_size != -1 && ret.size() > max_size)
				throw (std::overflow_error("overflow max_size in getStringFromFile"));
		}
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
	
	std::string containerToString(std::vector<unsigned char> container, std::string sep)
	{
        std::string ret;
		for (std::vector<unsigned char>::iterator it = container.begin(); it != container.end(); ++it)
		{
			ret.append(1, *it);
			if (++it != container.end())
				ret.append(sep);
			--it;
		}
		return (ret);
    }

	namespace {
		template<typename T>
		void addDevideResult(int& ret, T& data, int number)
		{
			ret += data / number;
			data %= number;
		}
		void makeTime(struct tm* t)
		{
			t->tm_mday++;
			t->tm_year -= 1900;
		}
	}
	void convertTimespecToTm(time_t s, struct tm* t)
	{
		ft::bzero(t, sizeof(struct tm));
		t->tm_gmtoff = 0;
		t->tm_isdst = 0;
		t->tm_zone = NULL;
		t->tm_year = 1970;
		t->tm_mon = 0;

		long data = s + 32400;
		if (data > 946684800) {
			t->tm_year = 2000;
			data -= 946684800;
		}
		ft::addDevideResult(t->tm_yday, data, 86400);
		ft::addDevideResult(t->tm_hour, data, 3600);
		ft::addDevideResult(t->tm_min, data, 60);
		t->tm_sec = data;
	
		while (t->tm_yday > 365) {
			if (t->tm_year % 4 == 0 && (t->tm_year % 100 != 0 || t->tm_year % 400 == 0)) {
				if (t->tm_yday == 366)
					break ;
				t->tm_yday--;
			}
			t->tm_yday -= 365;
			t->tm_year++;
		}
		int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		bool leap = t->tm_year % 4 == 0 && (t->tm_year % 100 != 0 || t->tm_year % 400 == 0);
		t->tm_mday = t->tm_yday;
		while (t->tm_mday > months[t->tm_mon])
		{
			if (leap && t->tm_mon == 2) {
				if (t->tm_mday == 28)
					break ;
				t->tm_mday--;
			}
			t->tm_mday -= months[t->tm_mon];
			t->tm_mon++;
		}
		t->tm_wday = t->tm_mday % 7;
		makeTime(t);
		return ;
	}
}
