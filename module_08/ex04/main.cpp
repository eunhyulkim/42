#include <string>
#include <iostream>

#include "includes/PolandMan.hpp"

int		main(int ac, char *av[])
{
    PolandMan pm;

    if (ac != 2)
        std::cout << "There should be one expressions." << std::endl;
    if (!pm.set_m_tokens(av[1]))
        std::cout << "expressions is unvalid" << std::endl;
    else
    {
        pm.printTokens("Tokens");
        pm.set_m_postfix();
        pm.printPostfix("Prefix");
        pm.runCalc();
        pm.printResult();
    }
    // else if (!pm.set_m_tokens(av[1]) || !pm.set_m_rpolish_expression())
    //     std::cout << "expressions is unvalid" << std::endl;
    // else
    //     pm.runCalc();

    return (0);
}
