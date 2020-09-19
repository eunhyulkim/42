#include <sys/select.h>
#include <iostream>
#include "ServerManager.hpp"

int main(int ac, char *av[], char **env)
{
    ServerManager manager;
    Config config("SOFTWARE_NAME: ft_nginx\nSOFTWARE_VERSION: 0.1\nHTTP_VERSION: 1.0\nCGI_VERSION: 1.1", env);
    manager.set_m_config(config);
    manager.fdSet(2, ServerManager::READ_SET);
    manager.fdSet(4, ServerManager::READ_SET);
    manager.fdSet(1, ServerManager::WRITE_SET);
    manager.fdSet(3, ServerManager::ERROR_SET);
    manager.fdSet(5, ServerManager::ERROR_COPY_SET);
    manager.fdSet(6, ServerManager::WRITE_COPY_SET);
    manager.fdCopy(ServerManager::READ_SET);
    manager.set_m_max_fd(6);
    manager.printFdSets();
    std::cout << manager.get_m_config() << std::endl;
    return (0);
}
