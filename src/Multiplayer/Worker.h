//
// Created by silvman on 16.05.18.
//

#ifndef SERVER_WORKER_H
#define SERVER_WORKER_H

#include "../Game.h"
#include "Entities/Player.h"

namespace mp {
    class worker {
        struct msg {
            static constexpr const char *success = "[worker:success] ";
            static constexpr const char *run = "[worker:run] ";
            static constexpr const char *end = "[worker:end] ";
        };

        pid_t               pid_;

        player &            first_;
        player &            second_;
        Game                game_;

    public:
        worker(player &first, player &second, pid_t pid);

        void work();
    };
}

#endif //SERVER_WORKER_H
