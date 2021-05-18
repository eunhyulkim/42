# include "test_main.hpp"

namespace {
    void print(std::string test_name) {
    std::cout << std::endl << "\033[1;36m" << std::setw(50) << std::left << test_name << "\033[0m" << std::endl << std::endl;
}
}

void container_test(std::string arg) {
    print(arg + " test start...");

    if (std::string(arg) == "vector")
        vector_test_main();
    else if (std::string(arg) == "stack")
        stack_test_main();
    else if (std::string(arg) == "list")
        list_test_main();
    else if (std::string(arg) == "queue")
        queue_test_main();
    else if (std::string(arg) == "map")
        map_test_main();
    else if (std::string(arg) == "deque")
        deque_test_main();
    else if (std::string(arg) == "multimap")
        multimap_test_main();
    else if (std::string(arg) == "set")
        set_test_main();
    else if (std::string(arg) == "multiset")
        multiset_test_main();
    else if (std::string(arg) == "all") {
        print("[Vector Container]");
        vector_test_main();
        print("[Stack Container]");
        stack_test_main();
        print("[List Container]");
        list_test_main();
        print("[Queue Container]");
        queue_test_main();
        print("[Map Container]");
        map_test_main();
        print("[Deque Container]");
        deque_test_main();
        print("[Multimap Container]");
        multimap_test_main();
        print("[Set Container]");
        set_test_main();
        print("[Multiset Container]");
        multiset_test_main();
    } else {
        std::cout << "Argument is unvalid." << std::endl;
    }
}

int main(int ac, char *av[]) {
    if (ac == 1) {
        std::cout << "Input container name what you want to test." << std::endl;
        return (0);
    } else if (ac == 3) {
        std::cout << "There must be one argument." << std::endl;
        return (0);
    }
    container_test(av[1]);
    return (0);
}
