//
// Created by silvman on 16.05.18.
//

#include "Event.h"

mp::Event::Event(int id, char type, const std::string &value, sf::Time time) :
        id(id),
        type(type),
        value(value),
        time(time) { }

mp::Event::Event(const std::string &sId, const std::string &sType, const std::string &value, const std::string &sTime) :
        id(0),
        type('\0'),
        value(value),
        time()
{
    id = atoi(sId.c_str());
    type = sType[0];

    unsigned long long temp_time = 0;
    for (auto &&digit : sTime) {
        temp_time *= 10;
        temp_time += digit - '0';
    }

    time = sf::microseconds(temp_time);
}

void mp::parseEventString(const std::string &sEvents, std::vector<mp::Event> &vEvents) {
    auto iterator = sEvents.begin();

    std::string str_num_events;
    for (; *iterator != ' '; ++iterator)
        str_num_events += *iterator;
    iterator++;

    int num_events = atoi(str_num_events.c_str());

    for (int i = 0; i < num_events; ++i) {
        std::string sId;
        std::string sType;
        std::string sValue;
        std::string sTime;

        for (; *iterator != ' '; ++iterator)
            sId += *iterator;
        ++iterator;

        for (; *iterator != ' '; ++iterator)
            sType += *iterator;
        ++iterator;

        for (; *iterator != ' '; ++iterator)
            sValue += *iterator;
        ++iterator;

        for (; *iterator != ' ' && iterator != sEvents.end(); ++iterator)
            sTime += *iterator;
        ++iterator;

        vEvents.emplace_back(sId, sType, sValue, sTime);
    }

}

void mp::encodeEventsToString(std::string &sEvents, std::vector<mp::Event> &vEvents) {
    sEvents.append(std::to_string(vEvents.size()) + " ");

    //  сборка сообщения, включающего все эвенты
    for (auto &&e : vEvents)
        sEvents.append(std::to_string(e.id) + " " + e.type + " " + e.value + " " + std::to_string(e.time.asMicroseconds()) + " ");

}