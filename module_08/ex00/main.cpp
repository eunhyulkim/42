#include "easyfind.hpp"
#include <iostream>
#include <set>

int		main(void)
{
	std::set<int> arr;
	for (int i = 0; i < 10; i++)
		arr.insert((i + 10) * 10);
	for (int i = 0; i < 10; i++)
	{
		try {
			std::cout << *(easyfind(arr, (i + 15) * 10)) << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
	return (0);
}
