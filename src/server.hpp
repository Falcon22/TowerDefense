//
// Created by silvman on 08.04.18.
//

#ifndef TOWERDEFENSE_SERVER_HPP
#define TOWERDEFENSE_SERVER_HPP

#include <SFML/Network.hpp>
#include "manager.hpp"

namespace server {
    class worker { // TODO singleton?
    private:
        sf::TcpListener     listener;
        sf::SocketSelector  selector;
        game_manager        pool_games;
        player_manager      pool_players;

        bool running;

    public:
        worker(const sf::IpAddress& ip, unsigned short port);
        ~worker();

        void work();

        void try_new_connection();
    };
}

#endif //TOWERDEFENSE_SERVER_HPP
