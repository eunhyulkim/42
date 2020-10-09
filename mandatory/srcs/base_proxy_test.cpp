# include "ServerManager.hpp"
# include "ProxyBase.hpp"

int main(void)
{
    ServerManager manager;
    std::string token;

    token = "host 127.0.0.1\n";
    token += "port 8080\n";
    token += "type filter\n";
    token += "server [127.0.0.1:8081]";
    try {
        ProxyBase proxy(&manager, token);
        proxy.runProxy();
    } catch (std::exception& e) {
        std::cout << "error:" << e.what() << std::endl;
    }
}
