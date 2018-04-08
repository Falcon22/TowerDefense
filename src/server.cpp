//
// Created by silvman on 08.04.18.
//

#include <iostream>
#include "server.hpp"

server::worker::worker(const sf::IpAddress &ip, unsigned short port): running(true) {
    listener.listen(port);
    selector.add(listener);
}

server::worker::~worker() {
    listener.close(); // TODO Нужно?
}

void server::worker::work() {
    std::cout << "[run]" << std::endl;
    while (running) {
        if (selector.wait(sf::seconds(0.1))) {
            if (selector.isReady(listener)) {
                try_new_connection();
            } else {
                // прием данных от игроков
            }
        } else {
            // отправка данных игрокам
        }
    }
}

void server::worker::try_new_connection() {
    player new_player; // TODO RAII (unique ptrs)
    if (listener.accept(new_player.getSocket()) == sf::Socket::Done) {
        selector.add(new_player.getSocket());
        pool_players.add(std::move(new_player));
        std::cout << "[success] connected player" << std::endl;
    } else {
        std::cout << "[fail] didn't connect player" << std::endl;
    }
}


