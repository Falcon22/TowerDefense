//
// Created by silvman on 16.05.18.
//

#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include "Entity.h"
#include <iostream>

namespace mp {
    class game : public entity {
    private:
        struct msg {
            static constexpr const char *game_running = "[game:fail] game already running" ;
        };

        std::string     name_;
        int             player_id_first_;
        int             player_id_second_;

        bool            first_connected_;
        bool            second_connected_;

        bool            is_started_;

    public:
        explicit game(const std::string& name);

        bool isReady() const;
        void join(int player_id);
        const std::string& getName() const;

        int getFirstId() const;

        int getSecondId() const;


        bool isStarted() const;
        void start();
    };
}

#endif //SERVER_GAME_H
