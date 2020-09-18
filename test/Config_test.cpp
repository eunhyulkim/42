#include "../includes/Config.hpp"
# include <string>
# include <iostream>
# include <fstream>
# include <cstdlib>
# include <iomanip>

int main(int ac, char *av[], char **env) {
    Config config("ft_nginx", "0.1", "1.0", "1.1", env);
    std::cout << config;
    return (0);
}
