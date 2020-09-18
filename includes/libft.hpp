#ifndef LIBFT_HPP
# define LIBFT_HPP

# include <string>
# include <iostream>
# include <vector>
# include <fcntl.h>
# include <unistd.h>

namespace ft {
    std::string getStringFromFile(std::string file_path);
    std::vector<std::string> split(std::string s, char c);
}

#endif
