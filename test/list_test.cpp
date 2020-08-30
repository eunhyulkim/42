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
	// print("[iterator] operator[]", ret[9]);
	// print("[iterator] operator[]", ret[10]);
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
	// print("[reverse-iterator] operator[]", ret[9]);
	// print("[reverse-iterator] operator[]", ret[10]);
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
	print("[container] empty", ret[8]);

    /* iterators test */
	print("[container] begin", ret[9]);
	print("[container] end", ret[10]);
	print("[container] rbegin", ret[11]);
	print("[container] rend", ret[12]);

	/* element access test */
	print("[container] front", ret[13]);
	print("[container] back", ret[14]);

    /* modifiers test */
	print("[container] assign iterator", ret[15]);
	print("[container] assign value(with n)", ret[16]);
	print("[container] push_front", ret[18]);
	print("[container] push_back", ret[17]);
	print("[container] pop_front", ret[19]);
	print("[container] pop_back", ret[20]);
	print("[container] insert value", ret[21]);
	print("[container] insert value(with n)", ret[22]);
	print("[container] insert iterator", ret[23]);
	print("[container] erase position", ret[24]);
	print("[container] erase iterator", ret[25]);
    print("[container] resize", ret[26]);
	print("[container] swap", ret[27]);
	print("[container] clear", ret[28]);

    /* operations */
    print("[container] splice(no param)", ret[29]);
    print("[container] splice(single iter)", ret[30]);
    print("[container] splice(range iter)", ret[31]);
    print("[container] remove", ret[32]);
    print("[container] remove_if", ret[33]);
    print("[container] unique", ret[34]);
    print("[container] unique(with BinaryPredicate)", ret[35]);
    print("[container] merge(no param)", ret[36]);
    print("[container] merge(with comp)", ret[37]);
    print("[container] sort(no param)", ret[38]);
    print("[container] sort(with comp)", ret[39]);
    print("[container] reverse", ret[41]);

    /* global test */
    print("[global] operator==", ret[42]);
    print("[global] operator!=", ret[43]);
    print("[global] operator<", ret[44]);
    print("[global] operator<=", ret[45]);
    print("[global] operator>", ret[46]);
    print("[global] operator>=", ret[47]);
    print("[global] swap", ret[48]);
}

bool remove_judge(const Myclass& obj) {
    return (obj.get_m_name() == "one");
}

bool sort_judge(const Myclass& lhs, const Myclass& rhs) {
    int lvalue = 0;
    int rvalue = 0;
    std::string name[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    for (int i = 0; i < 10; ++i) {
        if (name[i] == lhs.get_m_name())
            lvalue = i + 1;
        if (name[i] == rhs.get_m_name())
            rvalue = i + 1;
    }
    return (lvalue < rvalue);
}

bool unique_judge(const Myclass& lhs, const Myclass& rhs) {
    int lvalue = 0;
    int rvalue = 0;
    std::string name[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    for (int i = 0; i < 10; ++i) {
        if (name[i] == lhs.get_m_name())
            lvalue = i + 1;
        if (name[i] == rhs.get_m_name())
            rvalue = i + 1;
    }
    return (lvalue + 2 == rvalue);
}

}

int list_test_main(void)
{
    /* iterator test */
    {
        bool ret[50];
        Myclass data[10];
        for (int i = 0; i < 10; ++i)
            data[i] = Myclass(g_name[i]);
    
        ft::List<Myclass> *con = new ft::List<Myclass>;
        for (size_t i = 0; i < 20; i++) {
            con->push_back(data[i % 10]);
        }
        ft::List<Myclass>::const_iterator it_const = static_cast<const ft::List<Myclass> *>(con)->begin();
        ret[6] = it_const->get_m_name() == "zero";
        ft::List<Myclass>::iterator it_default;
        ret[0] = true;
        ft::List<Myclass>::iterator it_param((con->begin() + 2).as_node());
        ret[1] = ret[5] = (*it_param).get_m_name() == "two";
        ft::List<Myclass>::iterator it_copy(it_param);
        ret[2] = (*it_copy).get_m_name() == "two";
        ft::List<Myclass>::iterator it_assign((con->begin() + 1).as_node());
        it_default = it_assign;
        ret[3] = (*it_default).get_m_name() == "one";
        ret[8] = ret[7] = it_default->get_m_name() == "one";
        ret[10] = ret[9] = it_default.as_node()->next()->next()->value().get_m_name() == "three";
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
    
        ft::List<Myclass> *con = new ft::List<Myclass>;
        for (size_t i = 0; i < 20; i++) {
            con->push_back(data[i % 10]);
        }
        ft::List<Myclass>::reverse_iterator it_default;
        ret[0] = true;
        ft::List<Myclass>::iterator it_ref(con->begin() + 19);
        ft::List<Myclass>::reverse_iterator it_param(it_ref);
        ret[1] = ret[6] = ret[5] = (*it_param).get_m_name() == "eight";
        ft::List<Myclass>::reverse_iterator it_copy(it_param);
        ret[2] = (*it_copy).get_m_name() == "eight";
        ft::List<Myclass>::reverse_iterator it_assign(it_ref - 1);
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
        bool ret[60];
        Myclass data[10];
        for (int i = 0; i < 10; ++i)
            data[i] = Myclass(g_name[i]);
    
        ft::List<Myclass> *con = new ft::List<Myclass>;
        for (size_t i = 0; i < 20; i++) {
            con->push_back(data[i % 10]);
        }
        if (con->front().get_m_name() == "zero") {
            ret[13] = ret[0] = true;
        }
        ft::List<Myclass> param_con(2, data[1]);
        ret[16] = ret[17] = ret[1] = param_con.back().get_m_name() == "one";
        ft::List<Myclass> iter_con(con->begin(), con->end());
        ret[15] = ret[2] = iter_con.back().get_m_name() == "nine";
        ft::List<Myclass> copy_con(iter_con);
        ret[3] = copy_con.front().get_m_name() == "zero";
        ret[3] = (ret[3] == true) && (copy_con.back().get_m_name() == "nine");
        ft::List<Myclass> assign_con;
        assign_con = copy_con;
        ret[4] = assign_con.front().get_m_name() == "zero";
        ret[4] = (ret[4] == true) && (assign_con.back().get_m_name() == "nine");
        ret[6] = con->size() == 20;
        std::list<Myclass> pccon;
        ret[7] = pccon.max_size() == con->max_size();
        con->resize(21, data[0]);
        ret[14] = ret[26] = con->back().get_m_name() == "zero";
        con->resize(20);
        ret[26] = (ret[26] == true) && (con->size() == 20);
        ft::List<Myclass> empty_con;
        ret[8] = empty_con.empty();
        ret[9] = con->begin()->get_m_name() == "zero";
        ret[10] = (con->end() - 1)->get_m_name() == "nine";
        ret[11] = con->rbegin()->get_m_name() == "nine";
        ret[12] = (con->rend() - 1)->get_m_name() == "zero";
        con->push_front(data[2]);
        ret[18] = con->front().get_m_name() == "two";
        con->pop_front();
        ret[19] = con->front().get_m_name() == "zero";
        con->pop_back();
        ret[20] = con->back().get_m_name() == "eight";
        con->push_back(data[9]);
        con->insert(con->begin() + 2, data[9]);
        ret[21] = (con->begin() + 2)->get_m_name() == "nine";
        con->insert(con->begin() + 2, 2, data[4]);
        ret[22] = (con->begin() + 2)->get_m_name() == "four" && (con->begin() + 3)->get_m_name() == "four";
        con->insert(con->begin() + 2, iter_con.begin(), iter_con.begin() + 2);
        ret[23] = (con->begin() + 2)->get_m_name() == "zero" && (con->begin() + 3)->get_m_name() == "one";
        con->erase(con->begin() + 2);
        ret[24] = (con->begin() + 2)->get_m_name() == "one";
        con->erase(con->begin() + 2, con->begin() + 6);
        ret[25] = (con->begin() + 2)->get_m_name() == "two";
        ft::List<Myclass> swap_con;
        for (size_t i = 1; i < 21; i++) {
            swap_con.push_back(data[i % 10]);
        }
        con->swap(swap_con);
        ret[27] = (con->begin() + 1)->get_m_name() == "two" && (swap_con.begin() + 1)->get_m_name() == "one";
        swap(*con, swap_con);
        ret[48] = (con->begin() + 1)->get_m_name() == "one" && (swap_con.begin() + 1)->get_m_name() == "two";
        swap_con.clear();
        ret[28] = swap_con.size() == 0;

        ft::List<Myclass> splice_con;
        for (size_t i = 1; i < 4; i++) {
            splice_con.push_back(data[i]);
        }
        con->splice(con->begin(), splice_con);
        ret[29] = con->begin()->get_m_name() == "one" && (con->begin() + 1)->get_m_name() == "two";
        ret[29] = ret[29] == true && splice_con.empty();
        splice_con.splice(splice_con.begin(), *con, con->begin());
        ret[30] = con->begin()->get_m_name() == "two" && splice_con.begin()->get_m_name() == "one";
        splice_con.splice(splice_con.end(), *con, con->begin(), con->begin() + 2);
        ret[31] = con->begin()->get_m_name() == "zero" && (splice_con.end() - 1)->get_m_name() == "three";
        con->remove(data[0]);
        ret[32] = con->begin()->get_m_name() == "one" && (con->begin() + 9)->get_m_name() == "one";
        con->remove_if(remove_judge);
        ret[33] = con->begin()->get_m_name() == "two" && (con->begin() + 8)->get_m_name() == "two";
        con->sort();
        ret[38] = con->begin()->get_m_name() == "eight" && (con->end() - 1)->get_m_name() == "two";
        con->unique();
        ret[34] = con->begin()->get_m_name() == "eight" && (con->end() - 1)->get_m_name() == "two" && con->size() == 8;
        con->sort(sort_judge);
        ret[38] = con->begin()->get_m_name() == "two" && (con->end() - 1)->get_m_name() == "nine";
        con->insert(con->begin() + 1, data[4]);
        con->insert(con->begin() + 1, data[2]);
        con->insert(con->begin() + 3, data[1]);
        ret[39] = con->begin()->get_m_name() == "two" && (con->end() - 1)->get_m_name() == "nine";
        con->unique(unique_judge);
        ret[35] = (con->begin() + 1)->get_m_name() == "four" && (con->begin() + 2)->get_m_name() == "three";
        splice_con.clear();
        con->sort();
        ft::List<Myclass> backup_con(*con);
        splice_con.splice(splice_con.begin(), *con, con->begin() + 2, con->begin() + 5);
        con->merge(splice_con);
        // ret[36] = (con->begin() + 2)->get_m_name() == "four" && (con->begin() + 4)->get_m_name() == "nine";
        ret[36] = backup_con == *con;
        splice_con.splice(splice_con.begin(), *con, con->begin() + 2, con->begin() + 5);
        con->merge(splice_con, ft::less_than<Myclass>);
        ret[37] = backup_con == *con;
        con->reverse();
        ret[41] = (con->begin())->get_m_name() == "two" && (con->end() - 1)->get_m_name() == "eight";
        con->clear();
        for (size_t i = 0; i < 20; i++) {
            con->push_back(data[i % 10]);
        }

        ft::List<Myclass> *size_less = new ft::List<Myclass>;
        ft::List<Myclass> *size_more = new ft::List<Myclass>;
        ft::List<Myclass> *equal = new ft::List<Myclass>;
        ft::List<Myclass> *size_equal_fast = new ft::List<Myclass>;
        ft::List<Myclass> *size_equal_last = new ft::List<Myclass>;
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

        ret[42] = *con == *equal;
        ret[43] = *con != *size_less && *con != *size_more;
        ret[44] = !(*con < *equal) && (*con < *size_more) && !(*con < *size_less);
        ret[44] = ret[44] == true && !(*con < *size_equal_fast) && (*con < *size_equal_last);
        ret[45] = (*con <= *equal) && (*con <= *size_more) && !(*con <= *size_less);
        ret[45] = ret[45] == true && !(*con <= *size_equal_fast) && (*con <= *size_equal_last);
        ret[46] = !(*con > *equal) && !(*con > *size_more) && *con > *size_less;
        ret[46] = ret[46] == true && (*con > *size_equal_fast) && !(*con > *size_equal_last);
        ret[47] = (*con >= *equal) && !(*con >= *size_more) && *con >= *size_less;
        ret[47] = ret[47] == true && (*con >= *size_equal_fast) && !(*con >= *size_equal_last);

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
