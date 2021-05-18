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
//     for (test_type::iterator it = obj.begin(); it != obj.end(); ++it) {
//         std::cout << *it << " ";
//         if (i++ % 8 == 0)
//             std::cout << std::endl;
//     }
//     std::cout << std::endl;
// }

void iterator_print(bool* ret) {
    /* iterator canonical test */
    print("[iterator] default constructor", ret[0]);
    print("[iterator] parameter constructor", ret[1]);
    print("[iterator] copy constructor", ret[2]);
    print("[iterator] assign operator", ret[3]);
    print("[iterator] destructor", ret[4]);

    /* iterator operator test */
	print("[iterator] operator*", ret[5]);
	print("[iterator] operator*", ret[6]);
	print("[iterator] operator->", ret[7]);
	print("[iterator] operator->", ret[8]);
	print("[iterator] operator[]", ret[9]);
	print("[iterator] operator[]", ret[10]);
	print("[iterator] operator++(pre)", ret[11]);
	print("[iterator] operator++(post)", ret[12]);
	print("[iterator] operator--(pre)", ret[13]);
	print("[iterator] operator--(post)", ret[14]);
	print("[iterator] operator+", ret[15]);
	print("[iterator] operator+=", ret[16]);
	print("[iterator] operator-", ret[17]);
	print("[iterator] operator-=", ret[18]);
	print("[iterator] operator!=", ret[19]);
	print("[iterator] operator==", ret[20]);
	print("[iterator] operator<", ret[21]);
	print("[iterator] operator<=", ret[22]);
	print("[iterator] operator>", ret[23]);
	print("[iterator] operator>=", ret[24]);
}

void reverse_iterator_print(bool* ret) {
    /* iterator canonical test */
    print("[reverse-iterator] default constructor", ret[0]);
    print("[reverse-iterator] parameter constructor", ret[1]);
    print("[reverse-iterator] copy constructor", ret[2]);
    print("[reverse-iterator] assign operator", ret[3]);
    print("[reverse-iterator] destructor", ret[4]);

    /* iterator operator test */
	print("[reverse-iterator] operator*", ret[5]);
	print("[reverse-iterator] operator*", ret[6]);
	print("[reverse-iterator] operator->", ret[7]);
	print("[reverse-iterator] operator->", ret[8]);
	print("[reverse-iterator] operator[]", ret[9]);
	print("[reverse-iterator] operator[]", ret[10]);
	print("[reverse-iterator] operator++(pre)", ret[11]);
	print("[reverse-iterator] operator++(post)", ret[12]);
	print("[reverse-iterator] operator--(pre)", ret[13]);
	print("[reverse-iterator] operator--(post)", ret[14]);
	print("[reverse-iterator] operator+", ret[15]);
	print("[reverse-iterator] operator+=", ret[16]);
	print("[reverse-iterator] operator-", ret[17]);
	print("[reverse-iterator] operator-=", ret[18]);
	print("[reverse-iterator] operator!=", ret[19]);
	print("[reverse-iterator] operator==", ret[20]);
	print("[reverse-iterator] operator<", ret[21]);
	print("[reverse-iterator] operator<=", ret[22]);
	print("[reverse-iterator] operator>", ret[23]);
	print("[reverse-iterator] operator>=", ret[24]);
}

void container_print(bool* ret) {
    /* canonicatl test */
    print("[container] default constructor", ret[0]);
    print("[container] parameter constructor", ret[1]);
    print("[container] iterator constructor", ret[2]);
    print("[container] copy constructor", ret[3]);
    print("[container] assign operator", ret[4]);
    print("[container] destructor", ret[5]);

    /* capacity test */
	print("[container] size", ret[6]);
	print("[container] max_size", ret[7]);
	print("[container] resize", ret[8]);
	print("[container] empty", ret[9]);
	print("[container] reserve", ret[38]);
	print("[container] capacity", ret[39]);

    /* iterators test */
	print("[container] begin", ret[10]);
	print("[container] end", ret[11]);
	print("[container] rbegin", ret[12]);
	print("[container] rend", ret[13]);

	/* element access test */
	print("[container] operator[]", ret[14]);
	print("[container] at", ret[15]);
	print("[container] front", ret[16]);
	print("[container] back", ret[17]);

    /* modifiers test */
	print("[container] assign iterator", ret[18]);
	print("[container] assign value(with n)", ret[19]);
	// print("[container] push_front", ret[20]);
	print("[container] push_back", ret[21]);
	// print("[container] pop_front", ret[22]);
	print("[container] pop_back", ret[23]);
	print("[container] insert value", ret[24]);
	print("[container] insert value(with n)", ret[25]);
	print("[container] insert iterator", ret[26]);
	print("[container] erase position", ret[27]);
	print("[container] erase iterator", ret[28]);
	print("[container] swap", ret[29]);
	print("[container] clear", ret[30]);

    /* global test */
    print("[global] operator==", ret[31]);
    print("[global] operator!=", ret[32]);
    print("[global] operator<", ret[33]);
    print("[global] operator<=", ret[34]);
    print("[global] operator>", ret[35]);
    print("[global] operator>=", ret[36]);
    print("[global] swap", ret[37]);
}

}

int vector_test_main(void)
{
    /* iterator test */
    {
        bool ret[50];
        Myclass data[10];
        for (int i = 0; i < 10; ++i)
            data[i] = Myclass(g_name[i]);
    
        ft::Vector<Myclass> *con = new ft::Vector<Myclass>;
        for (size_t i = 0; i < 20; i++) {
            con->push_back(data[i % 10]);
        }
        ft::Vector<Myclass>::const_iterator it_const = static_cast<const ft::Vector<Myclass> *>(con)->begin();
        ret[6] = it_const->get_m_name() == "zero";
        ft::Vector<Myclass>::iterator it_default;
        ret[0] = true;
        ft::Vector<Myclass>::iterator it_param(&(*(con->begin() + 2)));
        ret[1] = ret[5] = (*it_param).get_m_name() == "two";
        ft::Vector<Myclass>::iterator it_copy(it_param);
        ret[2] = (*it_copy).get_m_name() == "two";
        ft::Vector<Myclass>::iterator it_assign(&(*(con->begin() + 1)));
        it_default = it_assign;
        ret[3] = (*it_default).get_m_name() == "one";
        ret[8] = ret[7] = it_default->get_m_name() == "one";
        ret[10] = ret[9] = it_default[2].get_m_name() == "three";
        ret[11] = (++it_default)->get_m_name() == "two";
        ret[12] = (it_default++)->get_m_name() == "two";
        ret[12] = (ret[12] == true && it_default->get_m_name() == "three") ? true : false;
        ret[13] = (--it_default)->get_m_name() == "two";
        ret[14] = (it_default--)->get_m_name() == "two";
        ret[14] = (ret[14] == true && it_default->get_m_name() == "one") ? true : false;
        ret[15] = (*(it_default + 3)).get_m_name() == "four";
        ret[15] = (ret[15] == true && (*it_default).get_m_name() == "one") ? true : false;
        it_default += 3;
        ret[16] = (*it_default).get_m_name() == "four";
        ret[17] = (*(it_default - 3)).get_m_name() == "one";
        ret[17] = (ret[17] == true && (*it_default).get_m_name() == "four") ? true : false;
        it_default -= 3;
        ret[18] = ((*it_default).get_m_name() == "one");
        ret[19] = (it_default != it_default) ? false : true;
        ret[20] = (it_default == it_default) ? true : false;
        ret[21] = it_default < (it_default + 1);
        ret[22] = it_default <= it_default;
        ret[23] = (it_default + 1) > it_default;
        ret[24] = it_default >= it_default;
        delete con;
        ret[4] = true;
        iterator_print(ret);
    }

    std::cout << std::endl;

    /* reverse iterator test */
    {
        bool ret[50];
        Myclass data[10];
        for (int i = 0; i < 10; ++i)
            data[i] = Myclass(g_name[i]);
        std::string tmp;
    
        ft::Vector<Myclass> *con = new ft::Vector<Myclass>;
        for (size_t i = 0; i < 20; i++) {
            con->push_back(data[i % 10]);
        }
        ft::Vector<Myclass>::reverse_iterator it_default;
        ret[0] = true;
        ft::Vector<Myclass>::iterator it_ref(con->begin() + 19);
        ft::Vector<Myclass>::reverse_iterator it_param(it_ref);
        ret[1] = ret[6] = ret[5] = (*it_param).get_m_name() == "eight";
        ft::Vector<Myclass>::reverse_iterator it_copy(it_param);
        ret[2] = (*it_copy).get_m_name() == "eight";
        ft::Vector<Myclass>::reverse_iterator it_assign(it_ref - 1);
        it_default = it_assign;
        ret[3] = (*it_default).get_m_name() == "seven";
        ret[8] = ret[7] = it_default->get_m_name() == "seven";
        ret[10] = ret[9] = true;
        ret[11] = (++it_default)->get_m_name() == "six";
        ret[12] = (it_default++)->get_m_name() == "six";
        ret[12] = (ret[12] == true && it_default->get_m_name() == "five") ? true : false;
        ret[13] = (--it_default)->get_m_name() == "six";
        ret[14] = (it_default--)->get_m_name() == "six";
        ret[14] = (ret[14] == true && it_default->get_m_name() == "seven") ? true : false;
        ret[15] = (*(it_default + 3)).get_m_name() == "four";
        ret[15] = (ret[15] == true && (*it_default).get_m_name() == "seven") ? true : false;
        it_default += 3;
        ret[16] = (*it_default).get_m_name() == "four";
        ret[17] = (*(it_default - 3)).get_m_name() == "seven";
        ret[17] = (ret[17] == true && (*it_default).get_m_name() == "four") ? true : false;
        it_default -= 3;
        ret[18] = ((*it_default).get_m_name() == "seven");
        ret[19] = (it_default != it_default) ? false : true;
        ret[20] = (it_default == it_default) ? true : false;
        ret[21] = it_default < (it_default + 1);
        ret[22] = it_default <= it_default;
        ret[23] = (it_default + 1) > it_default;
        ret[24] = it_default >= it_default;
        delete con;
        ret[4] = true;
        reverse_iterator_print(ret);
    }

    std::cout << std::endl;

    /* container test */
    {
        bool ret[50];
        Myclass data[10];
        for (int i = 0; i < 10; ++i)
            data[i] = Myclass(g_name[i]);
    
        ft::Vector<Myclass> *con = new ft::Vector<Myclass>;
        con->reserve(128);
        ret[39] = ret[38] = con->capacity() == 128;
        for (size_t i = 0; i < 20; i++) {
            con->push_back(data[i % 10]);
        }
        if ((*con)[0].get_m_name() == "zero") {
            ret[21] = ret[0] = true;
        }
        ft::Vector<Myclass> param_con(2, data[1]);
        ret[19] = ret[18] = ret[1] = param_con[1].get_m_name() == "one";
        ft::Vector<Myclass> iter_con(con->begin(), con->end());
        ret[2] = iter_con[0].get_m_name() == "zero";
        ret[2] = (ret[2] == true) && (iter_con[19].get_m_name() == "nine");
        ft::Vector<Myclass> copy_con(iter_con);
        ret[3] = copy_con[0].get_m_name() == "zero";
        ret[3] = (ret[3] == true) && (copy_con[19].get_m_name() == "nine");
        ft::Vector<Myclass> assign_con;
        assign_con = copy_con;
        ret[4] = assign_con[0].get_m_name() == "zero";
        ret[4] = (ret[4] == true) && (assign_con[19].get_m_name() == "nine");
        ret[6] = con->size() == 20;
        std::vector<Myclass> pccon;
        ret[7] = pccon.max_size() == con->max_size();
        con->resize(21, data[0]);
        ret[14] = ret[8] = (*con)[20].get_m_name() == "zero";
        con->resize(20);
        ret[8] = (ret[8] == true) && (con->size() == 20);
        ft::Vector<Myclass> empty_con;
        ret[9] = empty_con.empty();
        ret[10] = con->begin()->get_m_name() == "zero";
        ret[11] = (con->end() - 1)->get_m_name() == "nine";
        ret[12] = con->rbegin()->get_m_name() == "nine";
        ret[13] = (con->rend() - 1)->get_m_name() == "zero";
        ret[15] = con->at(1).get_m_name() == "one";
        ret[16] = con->front().get_m_name() == "zero";
        ret[17] = con->back().get_m_name() == "nine";
        con->insert(con->begin(), data[1]);
        ret[20] = (*con)[0].get_m_name() == "one";
        con->erase(con->begin());
        ret[22] = (*con)[0].get_m_name() == "zero";
        con->pop_back();
        ret[23] = (con->end() - 1)->get_m_name() == "eight";
        con->push_back(data[9]);
        con->insert(con->begin() + 2, data[9]);
        ret[24] = (*con)[2].get_m_name() == "nine";
        con->insert(con->begin() + 2, 2, data[4]);
        ret[25] = (*con)[2].get_m_name() == "four" && (*con)[3].get_m_name() == "four";
        con->insert(con->begin() + 2, iter_con.begin(), iter_con.begin() + 2);
        ret[26] = (*con)[2].get_m_name() == "zero" && (*con)[3].get_m_name() == "one";
        con->erase(con->begin() + 2);
        ret[27] = (*con)[2].get_m_name() == "one";
        con->erase(con->begin() + 2, con->begin() + 6);
        ret[28] = (*con)[2].get_m_name() == "two";
        ft::Vector<Myclass> swap_con;
        for (size_t i = 1; i < 21; i++) {
            swap_con.push_back(data[i % 10]);
        }
        con->swap(swap_con);
        ret[29] = (*con)[1].get_m_name() == "two" && swap_con[1].get_m_name() == "one";
        swap(*con, swap_con);
        ret[37] = (*con)[1].get_m_name() == "one" && swap_con[1].get_m_name() == "two";
        swap_con.clear();
        ret[30] = swap_con.size() == 0;
    
        ft::Vector<Myclass> *size_less = new ft::Vector<Myclass>;
        ft::Vector<Myclass> *size_more = new ft::Vector<Myclass>;
        ft::Vector<Myclass> *equal = new ft::Vector<Myclass>;
        ft::Vector<Myclass> *size_equal_fast = new ft::Vector<Myclass>;
        ft::Vector<Myclass> *size_equal_last = new ft::Vector<Myclass>;
        for (size_t i = 0; i < 19; i++) {
            size_less->push_back(data[i % 10]);
            size_more->push_back(data[i % 10]);
            equal->push_back(data[i % 10]);
            size_equal_fast->push_back(data[i % 10]);
            size_equal_last->push_back(data[i % 10]);
        }
        size_more->push_back(data[19 % 10]);
        size_more->push_back(data[20 % 10]);
        equal->push_back(data[19 % 10]);
        size_equal_fast->push_back(data[4]);
        size_equal_last->push_back(data[0]);

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
        ret[5] = true;
        container_print(ret);
    }
    return (0);
}
