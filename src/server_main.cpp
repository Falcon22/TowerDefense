//
// Created by silvman on 08.04.18.
//

#include <iostream>
#include "server.hpp"

int main () {
    // TODO чтение ip и порта из конфигов

    std::string     ip;
    unsigned short  port;

    std::cout << "[ip]: ";
    std::cin >> ip;

    std::cout << "[port]: ";
    std::cin >> port;

    try {
        server::worker worker(ip, port);
        worker.work();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}