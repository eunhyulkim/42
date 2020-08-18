# include <iostream>
# include <list>
# include "MutantStack.hpp"
# include <algorithm>

void	print(std::string msg) {
    std::cout << "\033[1;37;41m" << msg << "\033[0m";
}

int main(){

    print("MUTANTSTACK TEST START");

    MutantStack<int>    mstack;

    print("PUSH 5 AND 99"); std::cout << std::endl << std::endl;
    mstack.push(5);
    mstack.push(99);

    print("TOP:"); std::cout << mstack.top() << std::endl << std::endl;
    print("POP ELEMENT"); std::cout << std::endl << std::endl;
    mstack.pop();

    print("SIZE:"); std::cout << mstack.size() << std::endl << std::endl;

    print("PUSH 3, 5, 737, 0"); std::cout << std::endl << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    
    print("MIN:");  std::cout << static_cast<int>(*std::min_element(it, ite)) << std::endl;
    print("MAX:");  std::cout << static_cast<int>(*std::max_element(it, ite)) << std::endl << std::endl;

    ++it;
    --it;

    print("PRINT WITH ITERATOR"); std::cout << std::endl << std::endl;

    while(it != ite){
        std::cout << *it << std::endl;
        ++it;
    }
    
    std::stack<int> s(mstack);

    std::cout << std::endl;
    print("LIST TEST START");
    std::cout << std::endl;;

    std::list<int>    list;

    list.push_back(5);
    list.push_back(99);

    std::cout << "TOP = " << list.back() << std::endl;

    list.pop_back();

    std::cout << "Size = " << list.size() << std::endl;

    list.push_back(3);
    list.push_back(5);
    list.push_back(737);

    //[...]
    list.push_back(0);

    std::list<int>::iterator itlist = list.begin();
    std::list<int>::iterator itliste = list.end();

    ++itlist;
    --itlist;

    while(itlist != itliste){
        std::cout << *itlist << std::endl;
        ++itlist;
    }
    
    std::list<int> s2(list);

    return 0;
}
