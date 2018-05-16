//
// Created by silvman on 16.05.18.
//

#ifndef SERVER_CONSTANTS_H
#define SERVER_CONSTANTS_H

#include <SFML/System/Time.hpp>

class constants {
public:
    static inline sf::Time waitTime() {
        return sf::milliseconds(5);
    }

    static const unsigned short port = 55001;
    static const bool debug = true;
    static constexpr const char * ip = "0.0.0.0";

};

#endif //SERVER_CONSTANTS_H
