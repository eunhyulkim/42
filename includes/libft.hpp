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

namespace ft {
    void bzero(void *data, size_t len);
    std::string ltrim(std::string s, std::string seps = " ");
    std::string rtrim(std::string s, std::string seps = " ");
    std::string trim(std::string s, std::string seps = " ");
    std::string getStringFromFile(std::string file_path);
    std::vector<std::string> split(std::string s, char c = '\n');
    std::set<std::string> stringVectorToSet(std::vector<std::string> stringVector);
    std::map<std::string, std::string> stringVectorToMap(std::vector<std::string> stringVector, char sep = ':');
    std::string setToString(std::set<std::string> string_set, std::string sep = " ");

    template <typename T, typename V>
    bool hasKey(T& container, V& value) { return (container.find(value) != container.end()); }
}

#endif
