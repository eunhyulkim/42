# include <sys/time.h>
# include <iostream>
# include "Connection.hpp"

int main(void)
{
    Connection c(10, "127.0.0.1", 80);
    std::cout << c << std::endl;
    c.set_m_last_request_at();
    std::cout << c << std::endl;

    return (0);
}
