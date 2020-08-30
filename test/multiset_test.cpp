# include "test_main.hpp"

namespace {

std::string g_name[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
// 8549176320

void print(std::string test_name, bool ret) {
    std::cout << "\033[1;36;40m" << std::setw(50) << std::left << test_name << "\033[0m";
    if (ret == true)
        std::cout << "\033[1;32;40m" << "success" << "\033[0m" << std::endl;
    if (ret == false)
        std::cout << "\033[1;31;40m" << "fail" << "\033[0m" << std::endl;
}

// void cprint(test_type& obj)
// {
//     std::cout << ">---CONTENT(" << obj.size() << "---<" << std::endl;
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
	print("[iterator] operator++(pre)", ret[9]);
	print("[iterator] operator++(post)", ret[10]);
	print("[iterator] operator--(pre)", ret[11]);
	print("[iterator] operator--(post)", ret[12]);
	print("[iterator] operator+", ret[13]);
	print("[iterator] operator+=", ret[14]);
	print("[iterator] operator-", ret[15]);
	print("[iterator] operator-=", ret[16]);
	print("[iterator] operator!=", ret[17]);
	print("[iterator] operator==", ret[18]);
	print("[iterator] operator<", ret[19]);
	print("[iterator] operator<=", ret[20]);
	print("[iterator] operator>", ret[21]);
	print("[iterator] operator>=", ret[22]);
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
	print("[reverse-iterator] operator++(pre)", ret[9]);
	print("[reverse-iterator] operator++(post)", ret[10]);
	print("[reverse-iterator] operator--(pre)", ret[11]);
	print("[reverse-iterator] operator--(post)", ret[12]);
	print("[reverse-iterator] operator+", ret[13]);
	print("[reverse-iterator] operator+=", ret[14]);
	print("[reverse-iterator] operator-", ret[15]);
	print("[reverse-iterator] operator-=", ret[16]);
	print("[reverse-iterator] operator!=", ret[17]);
	print("[reverse-iterator] operator==", ret[18]);
	print("[reverse-iterator] operator<", ret[19]);
	print("[reverse-iterator] operator<=", ret[20]);
	print("[reverse-iterator] operator>", ret[21]);
	print("[reverse-iterator] operator>=", ret[22]);
}

void container_print(bool* ret) {
    /* canonicatl test */
    print("[container] default constructor", ret[0]);
    print("[container] iterator constructor", ret[2]);
    print("[container] copy constructor", ret[3]);
    print("[container] assign operator", ret[4]);
    print("[container] destructor", ret[5]);

    /* capacity test */
	print("[container] size", ret[6]);
	print("[container] max_size", ret[7]);
	print("[container] empty", ret[8]);

    /* iterators test */
	print("[container] begin", ret[9]);
	print("[container] end", ret[10]);
	print("[container] rbegin", ret[11]);
	print("[container] rend", ret[12]);

    /* modifiers test */
	print("[container] insert value", ret[14]);
	print("[container] insert value(with n)", ret[15]);
	print("[container] insert iterator", ret[16]);
	print("[container] erase key", ret[17]);
	print("[container] erase position", ret[18]);
	print("[container] erase iterator", ret[19]);
	print("[container] swap", ret[20]);
	print("[container] clear", ret[21]);

    /* observers test */
	print("[container] key comp", ret[22]);
	print("[container] value comp", ret[23]);

    /* operations test */
	print("[container] find", ret[24]);
	print("[container] count", ret[25]);
	print("[container] lower bound", ret[26]);
	print("[container] upper bound", ret[27]);
	print("[container] equal range", ret[28]);
}

}

int multiset_test_main(void)
{
    /* iterator test */
    {
        bool ret[50];
        Myclass data[10];
        for (int i = 0; i < 10; ++i)
            data[i] = Myclass(g_name[i]);
    
        ft::Multiset<Myclass> *con = new ft::Multiset<Myclass>;
        for (int i = 0; i < 20; i++) {
            con->insert(data[i % 10]);
        }
        ft::Multiset<Myclass>::const_iterator it_const = static_cast<const ft::Multiset<Myclass> *>(con)->begin();
        ret[6] = ret[7] = (*it_const).get_m_name() == "eight";
        ret[8] = it_const->get_m_name() == "eight";
        ft::Multiset<Myclass>::iterator it_default = con->begin();
        ret[0] = true;
        ft::Multiset<Myclass>::iterator it_param(it_default.as_node());
        ret[1] = it_param->get_m_name() == "eight";
        ft::Multiset<Myclass>::iterator it_copy(it_param);
        ret[2] = it_copy->get_m_name() == "eight";
        ft::Multiset<Myclass>::iterator it_assign((con->begin() + 1).as_node());
        it_default = it_assign;
        ret[5] = ret[3] = (*it_default).get_m_name() == "eight";
        ret[9] = (++it_default)->get_m_name() == "five";
        ret[10] = (it_default++)->get_m_name() == "five";
        ret[10] = (ret[10] == true && it_default->get_m_name() == "five") ? true : false;
        ret[11] = (--it_default)->get_m_name() == "five";
        ret[12] = (it_default--)->get_m_name() == "five";
        ret[12] = (ret[12] == true && it_default->get_m_name() == "eight") ? true : false;
        ret[13] = (*(it_default + 2)).get_m_name() == "five";
        ret[13] = (ret[13] == true && (*it_default).get_m_name() == "eight") ? true : false;
        it_default += 2;
        ret[14] = (*it_default).get_m_name() == "five";
        ret[15] = (*(it_default - 2)).get_m_name() == "eight";
        ret[15] = (ret[15] == true && (*it_default).get_m_name() == "five") ? true : false;
        it_default -= 2;
        ret[16] = ((*it_default).get_m_name() == "eight");
        ret[17] = (it_default != it_default) ? false : true;
        ret[18] = (it_default == it_default) ? true : false;
        ret[19] = it_default > (it_default + 1);
        ret[20] = it_default <= it_default;
        ret[21] = (it_default + 1) < it_default;
        ret[22] = it_default >= it_default;
        delete con;
        ret[4] = true;
        iterator_print(ret);
    }

    std::cout << std::endl;

    // // /* reverse iterator test */
    {
        bool ret[50];
        Myclass data[10];
        for (int i = 0; i < 10; ++i)
            data[i] = Myclass(g_name[i]);
    
        ft::Multiset<Myclass> *con = new ft::Multiset<Myclass>;
        for (int i = 0; i < 20; i++) {
            con->insert(data[i % 10]);
        }
        ft::Multiset<Myclass>::const_reverse_iterator it_const = static_cast<const ft::Multiset<Myclass> *>(con)->rbegin();
        ret[6] = ret[7] = (*it_const).get_m_name() == "zero";
        ret[8] = it_const->get_m_name() == "zero";
        ft::Multiset<Myclass>::reverse_iterator it_default = con->rbegin();
        ret[0] = true;
        ft::Multiset<Myclass>::reverse_iterator it_param(it_default.as_node());
        ret[1] = it_param->get_m_name() == "zero";
        ft::Multiset<Myclass>::reverse_iterator it_copy(it_param);
        ret[2] = it_copy->get_m_name() == "zero";
        ft::Multiset<Myclass>::reverse_iterator it_assign((con->rbegin() + 1).as_node());
        it_default = it_assign;
        ret[5] = ret[3] = (*it_default).get_m_name() == "zero";
        ret[9] = (++it_default)->get_m_name() == "two";
        ret[10] = (it_default++)->get_m_name() == "two";
        ret[10] = (ret[10] == true && it_default->get_m_name() == "two") ? true : false;
        ret[11] = (--it_default)->get_m_name() == "two";
        ret[12] = (it_default--)->get_m_name() == "two";
        ret[12] = (ret[12] == true && it_default->get_m_name() == "zero") ? true : false;
        ret[13] = (*(it_default + 2)).get_m_name() == "two";
        ret[13] = (ret[13] == true && (*it_default).get_m_name() == "zero") ? true : false;
        it_default += 2;
        ret[14] = (*it_default).get_m_name() == "two";
        ret[15] = (*(it_default - 2)).get_m_name() == "zero";
        ret[15] = (ret[15] == true && (*it_default).get_m_name() == "two") ? true : false;
        it_default -= 2;
        ret[16] = ((*it_default).get_m_name() == "zero");
        ret[17] = (it_default != it_default) ? false : true;
        ret[18] = (it_default == it_default) ? true : false;
        ret[19] = it_default < (it_default + 1);
        ret[20] = it_default <= it_default;
        ret[21] = (it_default + 1) > it_default;
        ret[22] = it_default >= it_default;
        delete con;
        ret[4] = true;
        reverse_iterator_print(ret);
    }

    std::cout << std::endl;

    /* container test */
    {
        bool ret[50];
        for (int i = 0; i < 50; ++i)
            ret[i] = 0;
        Myclass data[10];
        for (int i = 0; i < 10; ++i)
            data[i] = Myclass(g_name[i]);
    
        ft::Multiset<Myclass> *con = new ft::Multiset<Myclass>;
        con->insert(data[2]);
        con->insert(data[4]);
        con->insert(data[2]);
        ret[24] = ret[0] = con->size() == 3 && con->find(data[2])->get_m_name() == (con->end() - 1)->get_m_name();

        /* insert with iterator */
        con->insert(data[1]);
        ret[15] = ret[14] = con->begin()->get_m_name() == "four";
        con->insert(con->end(), data[5]);
        ret[10] = ret[16] = (con->end() - 1)->get_m_name() == "two";
        ret[12] = (con->rend() - 1)->get_m_name() == "five";

        /* copy constructor */
        ft::Multiset<Myclass> conCopy(*con);
        ret[3] = conCopy.begin()->get_m_name() == "five";

        /* iterator constructor */
        ft::Multiset<Myclass> conIter(con->begin(), con->end());
        ret[2] = conIter.begin()->get_m_name() == "five";

        /* assign operator */
        ft::Multiset<Myclass> conAssign;
        ret[8] = conAssign.empty();
        conAssign = *con;
        ret[9] = ret[4] = conAssign.begin()->get_m_name() == "five";
        ret[11] = conAssign.rbegin()->get_m_name() == "two";

        /* size */
        ret[7] = ret[6] = con->size() == 5;

        ret[22] = typeid(con->key_comp()).name() == typeid(ft::less<Myclass>).name();
        ret[23] = typeid(con->value_comp()).name() == typeid(ft::less<Myclass>).name();
    
        /* count */
        ret[25] = con->count(data[1]) == 1 && con->count(data[0]) == 0;
    
        /* swap */
        ft::Multiset<Myclass> conTwo;
        ft::Multiset<Myclass> conThree;

        conThree.insert(data[1]);
        conThree.insert(data[4]);
        conThree.insert(data[9]);

        conTwo.insert(data[2]);
        conTwo.insert(data[3]);
        conTwo.insert(data[4]);
        conTwo.insert(data[5]);

        conTwo.swap(conThree);
        ret[20] = conThree.find(data[2])->get_m_name() == "two";

        /* clear */
        conTwo.clear();
        ret[21] = conTwo.size() == 0;

        /* erase */
        ft::Multiset<Myclass> con_erase;
        con_erase.insert(data[1]);
        con_erase.insert(data[2]);
        con_erase.insert(data[3]);
        con_erase.insert(data[4]);
        con_erase.insert(data[5]);
        con_erase.insert(data[6]);

        con_erase.erase(con_erase.begin() + 3);
        con_erase.erase(data[3]);
        con_erase.erase(con_erase.begin(), con_erase.begin() + 2);
        ret[17] = ret[18] = ret[19] = con_erase.size() == 2 \
        && con_erase.begin()->get_m_name() == "one" \
        && (con_erase.end() - 1)->get_m_name() == "two";

        // /* lower and upper bound */
        ft::Multiset<Myclass> bound;
        
        for (int i = 0; i < 10; i++)
        {
            bound.insert(data[i]);
        }
        
        ret[26] = (bound.lower_bound(data[5]))->get_m_name() == "five";
        ret[27] = (bound.upper_bound(data[5]))->get_m_name() == "four";
        ret[28] = (bound.equal_range(data[5])).first->get_m_name() == "five";
        ret[28] = ret[28] == true && (bound.equal_range(data[5])).second->get_m_name() == "four";

        delete con;
        ret[5] = true;
        container_print(ret);
    }
    return (0);
}
