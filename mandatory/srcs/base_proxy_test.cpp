# include "ServerManager.hpp"
# include "ProxyBase.hpp"

int main(void)
{
    ServerManager manager;
    std::string token;

    token = "host 127.0.0.1\n";
    token += "port 8081\n";
    token += "type filter\n";
    token += "server [127.0.0.1:8080]";
    ProxyBase proxy(&manager, token);
    proxy.runProxy();
    return (0);
}
