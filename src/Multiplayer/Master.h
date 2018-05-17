//
// Created by silvman on 16.05.18.
//

#ifndef SERVER_MASTER_H
#define SERVER_MASTER_H

#include <SFML/Network.hpp>
#include "Entities/Game.h"
#include "Manager/PlayerManager.h"

namespace mp {
    class master { // TODO singleton?
    private:
        struct msg {
            static constexpr const char *run = "[master:run]";
            static constexpr const char *join = "[master:success] player join'd game ";
            static constexpr const char *add_game = "[master:success] add game ";
            static constexpr const char *success = "[master:success] ";
            static constexpr const char *error = "[master:error] fork failed";
            static constexpr const char *end = "[master:end]";
        };

        sf::TcpListener         listener_;
        sf::SocketSelector      selector_;
        std::vector<mp::game>   pool_games_;
        player_manager          pool_players_;
        bool                    running_;

        void proceedEvents(player &player);
        void startWorker(game& game);

    public:
        explicit master(unsigned short port = 55001);
        ~master();

        void work();
    };
}


#endif //SERVER_MASTER_H
