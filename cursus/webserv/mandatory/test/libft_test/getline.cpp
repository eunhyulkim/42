# include <string>
# include <iostream>
# include <fstream>
# include <cstdlib>
# include <iomanip>
# include <fcntl.h>
# include <unistd.h>
# include "libft.hpp"

int main(int ac, char *av[])
{
    char buff[1024];
    if (ac != 2)
        return (0);
    if (int fd = open(av[1], O_RDONLY) > 0)
    {
        int ret;
        while ((ret = ft::getline(fd, buff, sizeof(buff))) > 0) {
            std::cout << "ret: " << ret << std::endl;
            std::cout << buff << std::endl;
        }
        std::cout << "ret: " << ret << std::endl;
    }
    return (0);
}
