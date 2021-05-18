// int main(void)
// {
//     ServerManager manager;
//     std::string token;

//     token = "host 127.0.0.1\n";
//     token += "port 8084\n";
//     // token += "type filter\n";
//     token += "server [127.0.0.1:8081]\n"; // server [127.0.0.1:8081,127.0.0.1:8082] 처럼 바꾸기

//     token += "filter [[key1:val1|val2|val3], [key2:val1|val2|val3]]";

//     ServerManager::proxy_fd = open(PROXY_LOG_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0755);
//     try {
//         Proxy proxy(&manager, token);
//         proxy.runProxy();
//     } catch (std::exception& e) {
//         std::cout << "error:" << e.what() << std::endl;
//     }
// }

# include "ProxyManager.hpp"

int main(int ac, char *av[], char **env)
{
    ProxyManager manager;

    manager.openLog();
    if (ac > 2)
        manager.exitServer("There are many arguments.");
    else {
        try {
            if (ac == 2)
                manager.createServer(av[1], env);
            else
                manager.createServer(BONUS_CONFIG_FILE_PATH, env);
        } catch (std::exception& e) {
            manager.exitServer(e.what());
        }
    }
    try {
        manager.runServer();
    } catch (std::exception& e) {
        manager.exitServer(e.what());
    }
    exit(EXIT_SUCCESS);
}
