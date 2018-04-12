//
// Created by silvman on 08.04.18.
//

#ifndef TOWERDEFENSE_SERVER_HPP
#define TOWERDEFENSE_SERVER_HPP

#include <SFML/Network.hpp>
#include "manager.hpp"

class constants {
public:
    static sf::Time waitTime() {
        return sf::milliseconds(50);
    }

    static const unsigned short port = 55001;
};

namespace server {
    class worker { // TODO singleton?
    private:
        sf::TcpListener     listener;
        sf::SocketSelector  selector;
        game_manager        pool_games;
        player_manager      pool_players;
        std::vector<event>  players_input_events;
        std::vector<event>  players_output_events;
        bool                running;

        void tryNewConnection();
        void recievePlayerEvents();
        void recieveGamesEvents();
        void proceedEvents();
        void proceedGames();
        void sendPlayerEvents();
        void sendGamesEvents();

    public:
        worker(unsigned short port);
        ~worker();

        void work();
    };
}

#endif //TOWERDEFENSE_SERVER_HPP
