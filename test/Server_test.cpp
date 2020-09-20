#include "Server.hpp"
#include <iostream>
#include "libft.hpp"

int	main()
{
	std::vector<std::string> vec;
	std::string str = "location /a {\n"
        "	root /Users/gim-eunhyul/42seoul/subject/webserv\n"
        "	allow_method GET POST\n"
        "	auth_basic_realm \"access server a\"\n"
        "	auth_basic_file includes/libft.hpp\n"
        "	index index.html index.htm\n"
        "	autoindex on\n"
        "	cgi .php\n";
	std::string str1 = "location /abc {\n"
        "	root /Users/gim-eunhyul/42seoul/subject/webserv\n"
        "	allow_method GET POST\n"
        "	auth_basic_realm \"access server a\"\n"
        "	auth_basic_file includes/libft.hpp\n"
        "	index index.html index.htm\n"
        "	autoindex on\n"
        "	cgi .123php\n";

	std::string ser = "server_name default\n"
    "host 127.0.0.1\n"
    "port 80\n"
"\n"
    "REQUEST_URI_LIMIT_SIZE 1024\n"
    "REQUEST_HEADER_LIMIT_SIZE 256\n"
    "DEFAULT_ERROR_PAGE includes/libft.hpp\n"
    "LIMIT_CLIENT_BODY_SIZE 8192\n";

    // "}\n"
	// "location /abc {\n"
    //     "	root /Users/gim-eunhyul/42seoul/subject/webserv\n"
    //     "	allow_method GET POST\n"
    //     "	auth_basic_realm \"access server a\"\n"
    //     "	auth_basic_file includes/libft.hpp\n"
    //     "	index index.html index.htm\n"
    //     "	autoindex on\n"
    //     "	cgi .php\n"
    // "}\n";
	vec.push_back(str);
	vec.push_back(str1);

	// std::cout << ft::split(ft::split(str).front(), ' ')[1];
	// std::cout << str.substr(str.find('\n'));
	Server(NULL, 0, ser, vec, NULL);
	// while (str.find('}') != std::string::npos)
	// {
	// 	std::string tmp = str.substr(0, str.find('}') + 1);
	// 	std::cout << tmp;
	// 	std::cout << "\n--------\n";
	// 	str = str.substr(str.find('}') + 1);
	// }
	// std::string tmp1 = str.substr(str.find('}') + 1);
	// std::cout << tmp1;
}
