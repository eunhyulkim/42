#include <string>
#include <iostream>
#include <iomanip>
#include <random>
#include "Array.hpp"

void	print(std::string msg) {
    std::cout << "\033[1;37;41m" << msg << "\033[0m";
}

std::string get_random_name()
{
    std::string option_list[] =
    {
        "John", "Kane", "Anna", "Home", "Tue",
        "Samanda", "Ally", "Kai", "Soje", "Ellis",
        "Shiri", "Metue", "Tako", "Soo", "Haya",
        "Kie", "Suzu", "Nai", "Rika", "Tos"
    };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> name_dis(0, 19);
    return (option_list[name_dis(gen)]);
}
int		main(void)
{
    print("ALL TEST WITH INT"); std::cout << std::endl << std::endl;
    print("intArr"); std::cout << ": ";
    Array<int> intArr = Array<int>(4);
    Array<int> intArrTwo = Array<int>(5);
    Array<int> intArrThree = Array<int>(5);
    for (int i = 0; i < 5; i++)
    {
        try {
            intArrThree[i] = (i + 1) * 300;
            intArrTwo[i] = (i + 1) * 20;
            intArr[i] = (i + 1) * 10;
            std::cout << intArr[i] << " ";
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    print("intArrTwo"); std::cout << ": ";
    for (int i = 0; i < 5; i++)
        std::cout << intArrTwo[i] << " ";
    std::cout << std::endl;
    print("intArr(After Assign)"); std::cout << ": ";
    intArr = intArrTwo;
    for (int i = 0; i < 5; i++)
        std::cout << intArr[i] << " ";
    std::cout << std::endl;
    print("intArrTwo(After Assign)"); std::cout << ": ";
    for (int i = 0; i < 5; i++)
        std::cout << intArrTwo[i] << " ";
    std::cout << std::endl;
    print("intArrThree"); std::cout << ": ";
    for (int i = 0; i < 5; i++)
        std::cout << intArrThree[i] << " ";
    std::cout << std::endl;
    intArr = intArrThree;
    print("intArr(After Copy)"); std::cout << ": ";
    for (int i = 0; i < 5; i++)
        std::cout << intArr[i] << " ";
    std::cout << std::endl;
    print("intArrThree(After Copy)"); std::cout << ": ";
    for (int i = 0; i < 5; i++)
        std::cout << intArrThree[i] << " ";
    std::cout << std::endl << std::endl;
    
    print("OTHER TYPE DEFAULT TEST"); std::cout << std::endl << std::endl;
    print("charArr"); std::cout << ": ";
    Array<char> charArr = Array<char>(4);
    for (int i = 0; i < 5; i++)
    {
        try {
            charArr[i] = static_cast<char>(65 + i);
            std::cout << charArr[i] << " ";
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    print("floatArr"); std::cout << ": ";
    Array<float> floatArr = Array<float>(4);
    for (int i = 0; i < 5; i++)
    {
        try {
            floatArr[i] = 0.5f + i;
            std::cout << floatArr[i] << " ";
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    print("doubleArr"); std::cout << ": ";
    Array<double> doubleArr = Array<double>(4);
    for (int i = 0; i < 5; i++)
    {
        try {
            doubleArr[i] = 0.5 + i;
            std::cout << doubleArr[i] << " ";
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    print("stringArr"); std::cout << ": ";
    Array<std::string> stringArr = Array<std::string>(4);
    for (int i = 0; i < 5; i++)
    {
        try {
            stringArr[i] = get_random_name();
            std::cout << stringArr[i] << " ";
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    std::cout << std::endl;
    print("TEST END"); std::cout << std::endl;
    return (0);
}
