//
// Created by silvman on 16.05.18.
//

#include <iostream>
#include "Worker.h"

mp::worker::worker(player &first, player &second, pid_t pid)
        : first_(first), second_(second), pid_(pid), game_(first, second) {
    std::cout << msg::success << pid << std::endl;

    first_.setId(1);
    second_.setId(2);
}

void mp::worker::work() {
    std::cout << msg::run << pid_ << std::endl;

    // Отсылаем сообщения о начале игры (включает в себя айдишники)
    try {
        first_.startGame();
        second_.startGame();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return;
    }

    game_.server_run(false);

    std::cout << msg::end << pid_ << std::endl;
}