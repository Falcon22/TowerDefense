//
// Created by silvman on 08.04.18.
//

#ifndef TOWERDEFENSE_SERVER_HPP
#define TOWERDEFENSE_SERVER_HPP

#include <SFML/Network.hpp>
#include "Manager.h"

class constants {
public:
    static inline sf::Time waitTime() {
        return sf::milliseconds(5);
    }

    static const unsigned short port = 55001;
    static constexpr const char * ip = "0.0.0.0";
};

namespace mp {


    class master { // TODO singleton?
    private:
        sf::TcpListener         listener_;
        sf::SocketSelector      selector_;
        std::vector<mp::game>   pool_games_;
        player_manager          pool_players_;
        bool                    running_;

    public:
        explicit master(unsigned short port = 55001);
        ~master();

        void work();
    };

    class worker {
        sf::SocketSelector  selector_;
        bool                running_;

        player &            first_;
        player &            second_;

    public:
        explicit worker(player &first, player &second);

        void work();
    };
}

#endif //TOWERDEFENSE_SERVER_HPP
