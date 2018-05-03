//
// Created by silvman on 08.04.18.
//

#include <iostream>
#include "Server/Server.h"

int main () {
    // TODO чтение порта из конфигов

    try {
        mp::master master;
        master.work();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}