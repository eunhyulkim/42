#include "Location.hpp"
# include <string>
# include <iostream>
# include <fstream>
# include <cstdlib>
# include <iomanip>

void test(std::string& arg)
{
    std::cout << "[ARG]\n" << arg << std::endl << std::endl;
    Location location(arg);
    std::cout << "[RET]\n" << location;
}

int main(int ac, char *av[], char **env) {
    std::string normal_arg, twist_arg, empty_arg;

    normal_arg.append("\t\troot /var/www/html\n");
    normal_arg.append("\t\tallow_method GET HEAD POST\n");
    normal_arg.append("\t\tauth_basic_realm \"server_protect\"\n");
    normal_arg.append("\t\tauth_basic_file /var/auth/.httpd\n");
    normal_arg.append("\t\tindex index.htm index.html\n");
    normal_arg.append("\t\tcgi php\n");
    normal_arg.append("\t\tautoindex on\n");

    twist_arg.append("\t\t\troot    /var/www/html   \n");
    twist_arg.append("\t  allow_method    GET HEAD   POST\n");
    twist_arg.append("    auth_basic_realm \"server_protect\"\n");
    twist_arg.append("\t\tauth_basic_file  /var/auth/.httpd\n");
    twist_arg.append("\tindex index.htm    index.html\n");
    twist_arg.append("\t\t  cgi   php\n");
    twist_arg.append("\t\t  autoindex    on  \n");

    empty_arg.append("\t\t\troot    /var/www/html   \n");
    test(normal_arg);
    test(twist_arg);
    test(empty_arg);
    return (0);
}
