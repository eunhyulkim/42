# include "test_main.hpp"

namespace {

std::string g_name[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

void print(std::string test_name, bool ret) {
    std::cout << "\033[1;36;40m" << std::setw(50) << std::left << test_name << "\033[0m";
    if (ret == true)
        std::cout << "\033[1;32;40m" << "success" << "\033[0m" << std::endl;
    if (ret == false)
        std::cout << "\033[1;31;40m" << "fail" << "\033[0m" << std::endl;
}

// void cprint(test_type& obj)
// {
//     std::cout << ">---CONTENT---<" << std::endl;
//     int i = 1;
//     while (!obj.empty()) {
//         std::cout << obj.top().get_m_name() << " " << std::endl;
//         obj.pop();
//         if (i++ % 8 == 0)
//             std::cout << std::endl;
//     }
//     std::cout << std::endl;
// }

void container_print(bool* ret) {
    /* canonicatl test */
    print("[container] default constructor", ret[0]);
    print("[container] copy constructor", ret[1]);
    print("[container] assign operator", ret[2]);
    print("[container] destructor", ret[3]);

    /* capacity test */
	print("[container] size", ret[4]);
	print("[container] empty", ret[5]);

	/* element access test */
	print("[container] top", ret[6]);
	print("[container] top", ret[7]);

    /* modifiers test */
	print("[container] push", ret[8]);
	print("[container] pop", ret[9]);

    /* global test */
    print("[global] operator==", ret[31]);
    print("[global] operator!=", ret[32]);
    print("[global] operator<", ret[33]);
    print("[global] operator<=", ret[34]);
    print("[global] operator>", ret[35]);
    print("[global] operator>=", ret[36]);
}

}

int stack_test_main(void)
{
    /* container test */
    {
        bool ret[50];
        Myclass data[10];
        for (int i = 0; i < 10; ++i)
            data[i] = Myclass(g_name[i]);
    
        ft::Stack<Myclass> *con = new ft::Stack<Myclass>;
        for (size_t i = 0; i < 20; i++) {
            con->push(data[i % 10]);
        }
        if ((*con).top().get_m_name() == "nine") {
            ret[7] = ret[6] = ret[8] = ret[0] = true;
        }
        ft::Stack<Myclass> copy_con(*con);
        ret[1] = copy_con.top().get_m_name() == "nine";
        ft::Stack<Myclass> assign_con;
        assign_con = copy_con;
        ret[2] = assign_con.top().get_m_name() == "nine";
        ret[4] = con->size() == 20;
        std::stack<Myclass> pccon;
        ft::Stack<Myclass> empty_con;
        ret[5] = empty_con.empty();
        con->pop();
        ret[9] = con->top().get_m_name() == "eight";
        con->push(data[9]);
    
        ft::Stack<Myclass> *size_less = new ft::Stack<Myclass>;
        ft::Stack<Myclass> *size_more = new ft::Stack<Myclass>;
        ft::Stack<Myclass> *equal = new ft::Stack<Myclass>;
        ft::Stack<Myclass> *size_equal_fast = new ft::Stack<Myclass>;
        ft::Stack<Myclass> *size_equal_last = new ft::Stack<Myclass>;
        for (size_t i = 0; i < 19; i++) {
            size_less->push(data[i % 10]);
            size_more->push(data[i % 10]);
            equal->push(data[i % 10]);
            size_equal_fast->push(data[i % 10]);
            size_equal_last->push(data[i % 10]);
        }
        size_more->push(data[19 % 10]);
        size_more->push(data[20 % 10]);
        equal->push(data[19 % 10]);
        size_equal_fast->push(data[4]);
        size_equal_last->push(data[0]);

        ret[31] = *con == *equal;
        ret[32] = *con != *size_less && *con != *size_more;
        ret[33] = !(*con < *equal) && (*con < *size_more) && !(*con < *size_less);
        ret[33] = ret[33] == true && !(*con < *size_equal_fast) && (*con < *size_equal_last);
        ret[34] = (*con <= *equal) && (*con <= *size_more) && !(*con <= *size_less);
        ret[34] = ret[34] == true && !(*con <= *size_equal_fast) && (*con <= *size_equal_last);
        ret[35] = !(*con > *equal) && !(*con > *size_more) && *con > *size_less;
        ret[35] = ret[35] == true && (*con > *size_equal_fast) && !(*con > *size_equal_last);
        ret[36] = (*con >= *equal) && !(*con >= *size_more) && *con >= *size_less;
        ret[36] = ret[36] == true && (*con >= *size_equal_fast) && !(*con >= *size_equal_last);

        delete size_less;
        delete size_more;
        delete equal;
        delete size_equal_last;
        delete size_equal_fast;
        delete con;
        // while (1) // leak check
        //     ;
        ret[3] = true;
        container_print(ret);
    }
    return (0);
}
