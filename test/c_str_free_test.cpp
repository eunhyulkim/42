# include <string>
# include <iostream>
# include <fstream>
# include <cstdlib>
# include <iomanip>

int main(void)
{
    char *str = const_cast<char *>(std::string("abc").c_str());
    // free(str);
    return (0);
}
