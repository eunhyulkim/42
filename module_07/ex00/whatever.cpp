#include <iostream>
#include <string>
#include <iomanip>

void	print(std::string msg) {
    std::cout << "\033[1;37;41m" << std::setw(11) << msg << "\033[0m : ";
}

template <typename T>
void swap(T& a, T& b)
{
    T c = a;
    a = b;
    b = c;
    return ;
}

template <typename T>
T& min(T& a, T& b)
{
    return ((a < b) ? a : b);
}

template <typename T>
T& max(T& a, T& b)
{
    return ((a > b) ? a : b);
}

template <typename A>
void swap_test(A aa, A bb, std::string testname)
{
    print(testname);
    A a = aa;
    A b = bb;
    std::cout << std::setw(5) << a << "(" << static_cast<void *>(&a) << ") vs ";
    std::cout << std::setw(5) << b << "(" << static_cast<void *>(&b) << ") | ";
    ::swap<A>(a, b);
    std::cout << std::setw(5) << a << "(" << static_cast<void *>(&a) << ") vs ";
    std::cout << std::setw(5) << b << "(" << static_cast<void *>(&b) << ")" << std::endl;
}

template <typename A>
void min_test(A aa, A bb, std::string testname)
{
    print(testname);
    A a = aa, b = bb;
    A *c = &(::min<A>(a, b));
    std::cout << std::setw(5) << a << "(" << static_cast<void *>(&a) << ") vs ";
    std::cout << std::setw(5) << b << "(" << static_cast<void *>(&b) << ") | ";
    std::cout << *c << "(" << static_cast<void *>(c) << ")" << std::endl;
}

template <typename A>
void max_test(A aa, A bb, std::string testname)
{
    print(testname);
    A a = aa, b = bb;
    A *c = &(::max<A>(a, b));
    std::cout << std::setw(5) << a << "(" << static_cast<void *>(&a) << ") vs ";
    std::cout << std::setw(5) << b << "(" << static_cast<void *>(&b) << ") | ";
    std::cout << *c << "(" << static_cast<void *>(c) << ")" << std::endl;
}

int main(void)
{
    swap_test(-3, -5, "int swap");
    swap_test(-3, 5, "int swap");
    swap_test(3, -5, "int swap");
    swap_test(3, 5, "int swap");

    swap_test('A', 'B', "char swap");
    swap_test('B', 'A', "char swap");

    swap_test(32.2f, 31.2f, "float swap");
    swap_test(31.2f, 32.2f, "float swap");

    swap_test(32.2, 31.2, "double swap");
    swap_test(31.2, 32.2, "double swap");

    swap_test("aa", "bc", "string swap");
    swap_test("aa", "ab", "string swap");
    swap_test("abc", "ab", "string swap");
    swap_test("ab", "abc", "string swap");

    std::cout << std::endl;

    min_test(-3, -5, "int min");
    min_test(-3, 5, "int min");
    min_test(0, 0, "int min");
    min_test(3, -5, "int min");
    min_test(3, 5, "int min");

    min_test('A', 'B', "char min");
    min_test('B', 'A', "char min");
    min_test('A', 'A', "char min");

    min_test(32.2f, 31.2f, "float min");
    min_test(31.2f, 32.2f, "float min");
    min_test(32.2f, 32.2f, "float min");

    min_test(32.2, 31.2, "double min");
    min_test(31.2, 32.2, "double min");
    min_test(32.2, 32.2, "double min");

    min_test("aa", "bc", "string min");
    min_test("aa", "ab", "string min");
    min_test("abc", "ab", "string min");
    min_test("ab", "abc", "string min");
    min_test("abc", "abc", "string min");

    std::cout << std::endl;

    max_test(-3, -5, "int max");
    max_test(-3, 5, "int max");
    max_test(0, 0, "int max");
    max_test(3, -5, "int max");
    max_test(3, 5, "int max");

    max_test('A', 'B', "char max");
    max_test('B', 'A', "char max");
    max_test('A', 'A', "char max");

    max_test(32.2f, 31.2f, "float max");
    max_test(31.2f, 32.2f, "float max");
    max_test(32.2f, 32.2f, "float max");

    max_test(32.2, 31.2, "double max");
    max_test(31.2, 32.2, "double max");
    max_test(32.2, 32.2, "double max");

    max_test("aa", "bc", "string max");
    max_test("aa", "ab", "string max");
    max_test("abc", "ab", "string max");
    max_test("ab", "abc", "string max");
    max_test("abc", "abc", "string max");

    {
        int a = 2;
        int b = 3;
        ::swap( a, b );
        std::cout << "a = " << a << ", b = " << b << std::endl;
        std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
        std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
        std::string c = "chaine1";
        std::string d = "chaine2";
        ::swap(c, d);
        std::cout << "c = " << c << ", d = " << d << std::endl;
        std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
        std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
    }
    
    return (0);
}
