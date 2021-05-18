#include "../../includes/libft.hpp"
#include <vector>
#include <set>

int main(void)
{
    std::set<std::string> s;

    s.insert("data");
    std::cout << std::boolalpha << ft::hasKey(s, "date") << std::endl;
    std::cout << std::boolalpha << ft::hasKey(s, "dat") << std::endl;
    std::cout << std::boolalpha << ft::hasKey(s, "data") << std::endl;
    return (0);
}
