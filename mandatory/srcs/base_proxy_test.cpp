# include "ServerManager.hpp"
# include "ProxyBase.hpp"

int main(void)
{
    ServerManager manager;
    std::string token;

    token = "host 127.0.0.1\n";
    token += "port 8080\n";
    token += "type filter\n";
    token += "server [127.0.0.1:8082]";
    ServerManager::proxy_fd = open(PROXY_LOG_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0755);
    try {
        ProxyBase proxy(&manager, token);
        proxy.runProxy();
    } catch (std::exception& e) {
        std::cout << "error:" << e.what() << std::endl;
    }
}
