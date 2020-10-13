#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)
{
    unsigned int address = inet_addr("192.168.34.0");
    std::cout << address << std::endl;
    unsigned char bytes[4];
    std::string ret;
    ret = std::to_string(address & 0xFF) + ".";
    ret.append(std::to_string((address >> 8) & 0xFF) + ".");
    ret.append(std::to_string((address >> 16) & 0xFF) + ".");
    ret.append(std::to_string((address >> 24) & 0xFF));
    std::cout << ret << std::endl;
    return (0);
}
