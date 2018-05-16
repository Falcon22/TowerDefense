//
// Created by silvman on 16.05.18.
//

#ifndef SERVER_EVENT_H
#define SERVER_EVENT_H

#include <SFML/Network.hpp>

namespace mp {
    struct Event {
        int         id;
        char        type;
        std::string value;
        sf::Time    time;

        Event(int id, char type, const std::string &value, sf::Time time);
        Event(const std::string &sId, const std::string &sType, const std::string &value, const std::string &sTime);
    };

    void parseEventString(const std::string& sEvents, std::vector<mp::Event>& vEvents);
    void encodeEventsToString(std::string& sEvents, std::vector<mp::Event>& vEvents);
}


#endif //SERVER_EVENT_H
