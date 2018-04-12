//
// Created by silvman on 08.04.18.
//

#include <iostream>
#include "server.hpp"

int main () {
    // TODO чтение порта из конфигов
//
//    unsigned short  port;
//
//    std::cout << "[port]: ";
//    std::cin >> port;

    try {
        server::worker worker(constants::port);
        worker.work();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}