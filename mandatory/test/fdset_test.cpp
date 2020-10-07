
# include <fcntl.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <dirent.h>
# include <fcntl.h>
# include <unistd.h>

# include <cstdlib>
# include <cstring>
# include <iostream>
# include <algorithm>

# include <string>
# include <vector>
# include <queue>
# include <set>
# include <map>
# include "libft.hpp"

int main(void)
{
    fd_set s;
    fd_set c;

    FD_ZERO(&s);
    ft::fdZero(&c);
    FD_SET(5, &s);
    ft::fdSet(5, &c);
    for (int i = 0; i < 32; ++i) {
        std::cout << s.fds_bits[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 32; ++i) {
        std::cout << c.fds_bits[i] << " ";
    }
    return (0);
}
