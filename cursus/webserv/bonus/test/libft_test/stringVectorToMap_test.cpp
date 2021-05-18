# include <string>
# include <iostream>
# include <vector>
# include <map>
# include "libft.hpp"

int main(void) {
    std::vector<std::string> data;
    data.push_back("a : b");
    data.push_back("c: d");
    data.push_back("e :f");
    data.push_back("   g   :   h    ");
    data.push_back("    i:h    ");
    // data.push_back("g   -    h");
    try {
        std::map<std::string, std::string> ret = ft::stringVectorToMap(data);
        for (std::map<std::string, std::string>::iterator it = ret.begin(); it != ret.end(); ++it) {
            std::cout << it->first << " - " << it->second << std::endl;
        }
    } catch (std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return (0);
}
