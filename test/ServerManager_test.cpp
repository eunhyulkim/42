#include <sys/select.h>
#include <iostream>
#include "ServerManager.hpp"

int test_main(int ac, char *av[], char **env)
{
    ServerManager manager;
    if (false)
    {
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
    }

    if (ac == 2)
    {
        int ret = 0;
        std::string file = ft::getStringFromFile(av[1]);
        std::string config_block;
        std::vector<std::string> server_strings;
        std::cout << "PHASE 1" << std::endl;
        if (!manager.splitConfigString(file, config_block, server_strings))
            return (1);
        std::cout << "PHASE 2" << std::endl;
        if (!manager.isValidConfigBlock(config_block))
            return (2);
        std::cout << "PHASE 3" << std::endl;
        for (int i = 0; i < server_strings.size(); ++i)
        {
            std::string server_block;
            std::vector<std::string> location_blocks;
            std::cout << "PHASE 4-1" << std::endl;
            if (!manager.splitServerString(server_strings[i], server_block, location_blocks))
                return (3);
            std::cout << "PHASE 4-2" << std::endl;
            if (!manager.isValidServerBlock(server_block))
                return (4);
            std::cout << "PHASE 4-3" << std::endl;
            for (int j = 0; j < location_blocks.size(); ++j) {
                if (!manager.isValidLocationBlock(location_blocks[j]))
                    return (5);
            }
            std::cout << "PHASE 4-4" << std::endl;
            // manager.parseConfigBlock(config_block);
            // manager.parseServerBlock(server_block);
            // for (int j = 0; j < location_blocks.size(); ++j)
            //     manager.parseLocationBlock(location_blocks[j]);
            ++ret;
        }
    }
    return (0);
}

int main(int ac, char *av[], char **env)
{
    int ret = 0;
    if ((ret = test_main(ac, av, env)) == 0)
        std::cout << "CONFIG SUCCESS" << std::endl;
    else if (ret == 1)
        std::cout << "fail to splitConfigString" << std::endl;
    else if (ret == 2)
        std::cout << "fail to isValidConfigBlock" << std::endl;
    else if (ret == 3)
        std::cout << "fail to splitServerString" << std::endl;
    else if (ret == 4)
        std::cout << "fail to isValidServerBlock" << std::endl;
    else if (ret == 5)
        std::cout << "fail to isValidLocationBlock" << std::endl;
    return (0);
}
