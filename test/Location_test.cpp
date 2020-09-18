#include "Location.hpp"
# include <string>
# include <iostream>
# include <fstream>
# include <cstdlib>
# include <iomanip>

int main(int ac, char *av[], char **env) {
    std::string arg;
    arg.append("\t\troot /var/www/html\n");
    arg.append("\t\tallow_method GET HEAD POST\n");
    arg.append("\t\tauth_basic_realm \"server_protect\"\n");
    arg.append("\t\tauth_basic_file /var/auth/.httpd\n");
    arg.append("\t\tindex index.htm index.html\n");
    arg.append("\t\tcgi php\n");
    arg.append("\t\tautoindex on\n");

    std::cout << "[ARG]\n" << arg << std::endl << std::endl;
    Location location(arg);
    std::cout << "[RET]\n" << location;
    return (0);
}
