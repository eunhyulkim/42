#include <string>
#include <iostream>

#include "MindOpen.hpp"

int		main(int ac, char *av[])
{
    MindOpen mo;

    if (ac != 2)
        std::cout << "There should be one arguments." << std::endl;
    else if (!mo.set_m_raw_string(av[1]) || !mo.set_m_program())
        std::cout << "File is not opend or unvalid." << std::endl;
    else
        mo.runProgram();

    return (0);
}
