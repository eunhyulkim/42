#include "../includes/libft.hpp"
#include <iostream>

int main(int ac, char *av[]) {
    if (ac != 2)
        return (0);
    try {
        std::string ret = ft::getStringFromFile(av[1]);
        std::cout << ret << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
