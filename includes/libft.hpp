#ifndef LIBFT_HPP
# define LIBFT_HPP

# include <string>
# include <iostream>
# include <vector>
# include <fcntl.h>
# include <unistd.h>
# include <vector>
# include <set>
# include <map>
# include <exception>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <dirent.h>

namespace ft
{
    /* OLD LIBFT */
    void bzero(void *data, size_t len);
    void *memcpy(void *dest, const void *src, size_t len);
    void *calloc(size_t size, size_t count);
    char *strdup(const char *s);
    int free(void *ptr);
    int freeStr(char **str);
    int freeDoublestr(char ***doublestr_addr);
    size_t strlen(const char *s);
    char *strchr(const char *s, int c);
    char *strsub(char const *s, unsigned int start, size_t len);
    char *strsjoin(std::string s1 = "", std::string s2 = "", std::string s3 = "", std::string s4 = "", std::string s5 = ""); 
    int startswith(const char *str, const char *sub);
    int lenDoubleStr(char **str);
    size_t pow(size_t root, size_t square);
    std::string itos(std::string number, size_t from, size_t to);

    /* C++ LIBFT */
    std::string ltrim(std::string s, std::string seps = " ");
    std::string rtrim(std::string s, std::string seps = " ");
    std::string trim(std::string s, std::string seps = " ");
    std::string getStringFromFile(std::string file_path, int max_size = -1);
    std::string getStringFromFd(int fd, int max_size = -1);
    std::vector<std::string> split(std::string s, char c = '\n');
    std::set<std::string> stringVectorToSet(std::vector<std::string> stringVector);
    std::map<std::string, std::string> stringVectorToMap(std::vector<std::string> stringVector, char sep = ':');
    std::string containerToString(std::vector<unsigned char> container, std::string sep = "");
    int getline(int fd, char *line, int max_buffer_size);
    bool isFile(std::string path);
    bool isDirectory(std::string path);
    
    /* TCP function */
    void convertTimespecToTm(time_t s, struct tm* t);
	unsigned long ws_htonl(unsigned long x);
	unsigned short ws_htons(unsigned short x);

    /* Log util function */
    bool isRightTime(int second);
    void log(int access_fd, int error_fd, std::string text);

    /* Fdset operator */
	void fdZero(fd_set *x);
	void fdSet(int fd, fd_set *x);
	int fdIsset(int fd, fd_set *x);
	void fdClr(int fd, fd_set *x);
    std::string getSetFdString(int max_fd, fd_set* fset);

    /* Template function */
    template <typename T, typename V>
    bool hasKey(T container, V value) { return (container.find(value) != container.end()); }
    
    template <typename T>
    std::string containerToString(T container, std::string sep = " ")
    {
        std::string ret;
		for (typename T::iterator it = container.begin(); it != container.end(); it++)
		{
			ret.append(*it);
			if (++it != container.end())
				ret.append(sep);
			--it;
		}
		return (ret);
    }
}

#endif
