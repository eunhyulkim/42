# include "ServerManager.hpp"

int main(int ac, char *av[], char **env)
{
    ServerManager manager;

    manager.openLog();
    if (ac > 2)
        manager.exitServer("There are many arguments.");
    else {
        try {
            if (ac == 2)
                manager.createServer(av[1], env);
            else
                manager.createServer(DEFAULT_CONFIG_FILE_PATH, env);
        } catch (std::exception& e) {
            manager.exitServer(e.what());
        }
    }
    manager.runServer();
    exit(EXIT_SUCCESS);
}
