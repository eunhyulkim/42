#ifndef LIBFT_HPP
# define LIBFT_HPP

# include <string>
# include <iostream>
# include <fcntl.h>
# include <unistd.h>
# include <vector>
# include <set>
# include <map>
# include <exception>

namespace ft {
    std::string getStringFromFile(std::string file_path);
    std::string ltrim(std::string s, std::string seps = " ");
    std::string rtrim(std::string s, std::string seps = " ");
    std::string trim(std::string s, std::string seps = " ");
    std::set<std::string> stringVectorToSet(std::vector<std::string> stringVector);
    std::map<std::string, std::string> stringVectorToMap(std::vector<std::string> stringVector, char sep = ':');
    std::string setToString(std::set<std::string> string_set, std::string sep = " ");
}

#endif
