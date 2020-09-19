#include "../includes/Config.hpp"
# include <string>
# include <iostream>

int main(int ac, char *av[], char **env) {
    Config config("SOFTWARE_NAME: ft_nginx\nSOFTWARE_VERSION: 0.1\nHTTP_VERSION: 1.0\nCGI_VERSION: 1.1", env);
    std::cout << config;
    return (0);
}
