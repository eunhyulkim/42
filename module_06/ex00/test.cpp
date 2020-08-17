#include <string>
#include <iostream>
#include <limits>
#include <cmath>
#include <sstream>
#include "convert.hpp"

int main(void)
{
    std::cout << std::stod("1241vgh.0") << std::endl;
    std::cout << std::stod("1241vgh.") << std::endl;
    std::cout << std::stod("1241vgh") << std::endl;
    float d = -2147483649.0f;
    std::cout << d << std::endl;
    return (0);
}
