# include "webserv.hpp"

int main(int ac, char *av[], char **env)
{
    ServerManager manager;

    if (ac > 2)
        manager.exitServer("There are many arguments.");
    else {
        try {
            if (ac == 2)
                manager.createServer(av[1]);
            else
                manager.createServer(DEFAULT_CONFIG_FILE_PATH);
        } catch (std::exception& e) {
            manager.exitServer(e.what());
        }
    }
    std::filebuf
    std::cout
    manager.openLog();
    manager.runServer();
    exit(EXIT_SUCCESS);
}
