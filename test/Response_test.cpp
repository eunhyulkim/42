// #include "Response.hpp"
#include <iostream>
#include <map>
#include <cstdlib>
#include "Response.hpp"

int	main(void)
{
	Response test(NULL, 200, "test");
	test.addHeader("one", "two");

	test.addHeader("Transfer-encoding", "chunked");
	std::cout << test;
	// std::cout << test.c_str();
	// std::cout << test;
}
