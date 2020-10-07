# include <string>
# include <iostream>
# include <fstream>
# include <cstdlib>
# include <iomanip>

int main(void)
{
    std::cout << std::stoi(std::string("a"), 0, 16) << std::endl;
    return (0);
}
