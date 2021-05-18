#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <regex>

int		main(int ac, char *av[])
{
    if (ac != 3)
        return (0);
    std::string uri = av[1];
    std::string re = av[2];
    std::smatch match;
    std::regex regexp(re, std::regex::icase);
    if (std::regex_search(uri, match, regexp) && match.prefix().str().empty())
    {
        std::cout << "prefix: " << match.prefix().str() << std::endl;
        std::cout << "match: " << match.str() << std::endl;
        std::cout << "suffix: " << match.suffix().str() << std::endl;
    }
    else
        std::cout << "not matched" << std::endl;
    return (0);
}
