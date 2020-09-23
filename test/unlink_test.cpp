# include <string>
# include <iostream>
# include <fstream>
# include <cstdlib>
# include <iomanip>
# include <fcntl.h>
# include <unistd.h>

int main(int ac, char* av[])
{
    if (ac != 2)
        return (0);
    unlink(av[1]);
    return (0);
}
