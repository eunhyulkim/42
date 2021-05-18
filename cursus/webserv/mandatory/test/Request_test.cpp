#include "../includes/Request.hpp"
#include <iostream>

int main(void)
{
	Request a(NULL, NULL, "HEAD /Users/yopark HTTP/1.1");

	a.add_header("cONtent-tYpe   :     chunked");
	a.add_content("<!DOCTYPE html>\r\n");
	a.add_content("<body></body>\r\n");

	std::cout << a << std::endl;
	return (0);
}