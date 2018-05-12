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

    class worker {
        struct msg {
            static constexpr const char *success = "[worker:success] ";
            static constexpr const char *run = "[worker:run] ";
            static constexpr const char *end = "[worker:end] ";
        };

        sf::SocketSelector  selector_;
        bool                running_;
        pid_t               pid_;

        player &            first_;
        player &            second_;

    public:
        worker(player &first, player &second, pid_t pid);

        void work();
    };
}

#endif //TOWERDEFENSE_SERVER_HPP
