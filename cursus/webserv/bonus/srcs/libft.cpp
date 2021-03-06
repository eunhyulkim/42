#include "libft.hpp"

namespace ft
{

/* ************************************************************************** */
/* -------------------------------- OLD LIBFT ------------------------------- */
/* ************************************************************************** */

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
			std::free(ptr);
		return (1);
	}

	int
	freeStr(char **str)
	{
		if (!str || !(*str))
			return (0);
		ft::free(*str);
		*str = 0;
		return (1);
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

	size_t
	strlen(const char *s)
	{
		size_t i = 0;

		while (s[i] != '\0')
			i++;
		return (i);
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

	char
	*strsjoin(std::string s1, std::string s2, std::string s3, std::string s4, std::string s5)
	{
		s1.append(s2);
		s1.append(s3);
		s1.append(s4);
		s1.append(s5);
		return (strdup(s1.c_str()));
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

	size_t
	pow(size_t root, size_t square) {
		size_t idx = 0;
		size_t ret = 1;
		while (idx++ < square) {
			ret *= root;
		}
		return (ret);
	}

	long long int abs(long long int num)
	{
		if (num < 0)
				return (num * -1);
		return (num);
	}

	std::string
	to_string(long long int n)
	{
        long long int   nb;
        std::string		str;

		if (n == 0)
			return ("0");
        nb = n;
        while (nb != 0)
        {
            str.insert(str.begin(), static_cast<char>((ft::abs(nb % 10) + 48)));
            nb = nb / 10;
        }
		if (n < 0)
			str.insert(str.begin(), '-');
        return (str);
	}

	int stoi(std::string str, size_t base)
	{
        int sign = 1;
        long long value = 0;
		long long int_max = INT_MAX;
		std::string digit = "0123456789abcdefghijklmnopqrstuvwxyz";

        if (str.empty())
            return (0);
		if (str[0] == '-')
			sign = -1;
		if (str[0] == '-' || str[0] == '+')
			str.erase(str.begin());
        if (str.empty() || digit.find(str[0]) == std::string::npos)
            return (0);
        while (!str.empty() && digit.find(str[0]) < base)
        {
            value *= base;
            value += digit.find(str[0]);
			if ((sign == 1 && value > int_max) || (sign == -1 && value > int_max + 1))
				throw (std::overflow_error("stoi overflow"));
            str.erase(str.begin());
        }
        return (static_cast<int>(sign * value));
	}

	std::string
	itos(std::string number, size_t from, size_t to)
	{
		std::string base = "0123456789abcdefghijklmnopqrstuvwxyz";
		std::string ret = "";
		bool sign = false;
		size_t data = ft::stoi(number, from);

		if (number.empty() || data == 0)
			return ("0");
		if (data < 0)
		{
			data *= -1;
			sign = true;
		}
		while (data > 0)
		{
			ret.insert(ret.begin(), base[data % to]);
			data /= to;
		}
		return (ret);
	}
/* ************************************************************************** */
/* -------------------------------- C++ LIBFT ------------------------------- */
/* ************************************************************************** */

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
	getStringFromFile(std::string file_path, int max_size)
	{
		int fd = -1;
		size_t read_cnt = 0;
		char buff[1024];
		std::string ret;

		if ((fd = open(file_path.c_str(), O_RDONLY)) == -1)
			throw (std::invalid_argument("Failed open to " + file_path));
		while ((read_cnt = read(fd, buff, 1024)) > 0) {
			ret.append(buff, read_cnt);
			if (max_size != -1 && static_cast<int>(ret.size()) > max_size)
				throw (std::overflow_error("overflow max_size in getStringFromFile"));
		}
		close(fd);
		return (ret);
	}

	std::string
	getStringFromFd(int fd, int max_size)
	{
		int read_cnt = 0;
		char buff[1024];
		std::string ret;

		while ((read_cnt = read(fd, buff, 1024)) > 0) {
			ret.append(buff, read_cnt);
			if (max_size != -1 && static_cast<int>(ret.size()) > max_size)
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

		for (size_t i = 0; i < stringVector.size(); ++i) {
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
		for (size_t i = 0; i < stringVector.size(); ++i)
		{
			if (stringVector[i].empty())
				continue ;
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
		for (std::vector<unsigned char>::iterator it = container.begin(); it != container.end(); it++)
		{
			ret.append(1, *it);
			if (++it != container.end())
				ret.append(sep);
			--it;
		}
		return (ret);
    }

	int getline(int fd, char* line, int buffer_size)
	{
		int idx = 0;
		int len = -1;
		if ((len = recv(fd, line, buffer_size, MSG_PEEK)) == -1)
			return (-1);
		while (idx < len && line[idx] != '\n')
			++idx;
		if (line[idx] != '\n')
			return (len * -1);
		read(fd, line, idx + 1);
		line[idx] = '\0';
		if (idx > 0 && line[idx - 1] == '\r')
			line[--idx] = '\0';
		return (idx);
	}

	int getline(std::string& data, std::string& line, size_t buffer_size)
	{
		if (data.find("\n") == std::string::npos || data.find("\n") > buffer_size)
		{
			if (data.size() >= buffer_size)
				throw (std::overflow_error("line size is greather than buffer size"));
			else
				return (-1);
		}
		int pos = data.find("\n");
		line = data.substr(0, pos);
		line = rtrim(line, "\r");
		data.erase(0, pos + 1);
		return (line.size());
	}

	int getline(std::string& data, std::string& line)
	{
		if (data.find("\n") == std::string::npos)
			return (0);
		int pos = data.find("\n");
		line = data.substr(0, pos);
		line = rtrim(line, "\r");
		data.erase(0, pos + 1);
		return (1);
	}

	bool isFile(std::string path)
	{
		struct stat buf;
		stat(path.c_str(), &buf);
		return (S_ISREG(buf.st_mode));
	}

	bool isDirectory(std::string path)
	{
		struct stat buf;
		stat(path.c_str(), &buf);
		return (S_ISDIR(buf.st_mode));
	}
/* ************************************************************************** */
/* ------------------------------ TCP FUNCTION ------------------------------ */
/* ************************************************************************** */

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

	unsigned long ws_htonl(unsigned long x)
	{
		unsigned int a = 0x11223344;
		if (*(unsigned char*)&a == 0x11)
			return (x);

		return ((x & 0x000000ffU) << 24 | (x & 0x0000ff00U) << 8 | (x & 0x00ff0000U) >> 8 | (x & 0xff000000U) >> 24);
	}

	unsigned short ws_htons(unsigned short x)
	{
		unsigned int a = 0x11223344;
		if (*(unsigned char*)&a == 0x11)
			return (x);

		return ((x & 0x00ffU) << 8 | (x & 0xff00U) >> 8);
	}

	std::string
	inet_ntoa(unsigned int address)
	{
		std::string ret;

		ret = ft::to_string(address & 0xFF) + ".";
		ret.append(ft::to_string((address >> 8) & 0xFF) + ".");
		ret.append(ft::to_string((address >> 16) & 0xFF) + ".");
		ret.append(ft::to_string((address >> 24) & 0xFF));
		return (ret);
	}

/* ************************************************************************** */
/* ---------------------------- FDSET OPERATOR ------------------------------ */
/* ************************************************************************** */

	void fdZero(fd_set *x)
	{
		for (int i = 0 ; i < 32 ; ++i)
			x->fds_bits[i] = 0;
	}

	void fdSet(int fd, fd_set *x)
	{
		if (!(0 <= fd && fd < 1024))
			return ;
		int mask = 1 << fd % 32;
		x->fds_bits[fd / 32] |= mask;
	}

	int fdIsset(int fd, fd_set *x)
	{
		if (!(0 <= fd && fd < 1024))
			return (0);
		int mask = 1 << fd % 32;
		return (x->fds_bits[fd / 32] & mask);
	}

	void fdClr(int fd, fd_set *x)
	{
		if (!(0 <= fd && fd < 1024))
			return ;
		int mask = 1 << fd % 32;
		mask = ~mask;
		x->fds_bits[fd / 32] &= mask;
	}

	std::string
	getSetFdString(int max_fd, fd_set* fset)
	{
		std::string ret;
		bool first = true;
		for (int i = 0; i <= max_fd; ++i) {
			if (ft::fdIsset(i, fset)) {
				if (!first) {
					ret.append(",");
				}
				first = false;
				ret.append(ft::to_string(i));
			}
		}
		return (ret);
	}

/* ************************************************************************** */
/* --------------------------- LOG UTIL FUNCTION ---------------------------- */
/* ************************************************************************** */

	void log(int log_fd, std::string text) {
		if (log_fd != -1)
			write(log_fd, text.c_str(), text.size());
	}

	bool isRightTime(int second) {
		timeval t;
		gettimeofday(&t, NULL);
		if (t.tv_sec % second == 0 && t.tv_usec == 0)
			return (true);
		return (false);
	}

	std::string	getTimestamp(void)
	{
		std::time_t	t = std::time(0);
		std::tm* now = std::localtime(&t);
		std::string ret;
		ret.append("[" + ft::to_string(now->tm_year + 1900));
		ret.append(ft::to_string(now->tm_mon + 1));
		ret.append(ft::to_string(now->tm_mday) + "_");
		ret.append(ft::to_string(now->tm_hour) + "_");
		ret.append(ft::to_string(now->tm_min) + "_");
		ret.append(ft::to_string(now->tm_sec) + "]");
		return (ret);
	}

	std::string getSpeed(timeval from)
	{
		timeval t;
		gettimeofday(&t, NULL);
		return (ft::to_string((t.tv_sec - from.tv_sec) * 1000000 + (t.tv_usec - from.tv_usec)));
	}
}
