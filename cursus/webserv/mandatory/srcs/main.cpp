/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 04:38:53 by eunhkim           #+#    #+#             */
/*   Updated: 2020/10/20 02:04:41 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    try {
        manager.runServer();
    } catch (std::exception& e) {
        manager.exitServer(e.what());
    }
    exit(EXIT_SUCCESS);
}
