# include <string>
# include <iostream>
# include <fstream>
# include <cstdlib>
# include <iomanip>

int main(void)
{
    std::string data[][2] =
    {{"a", "b"},
    {"c", "d"}};

    std::cout << data[1][1] << std::endl;
}
