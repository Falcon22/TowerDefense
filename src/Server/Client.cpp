//
// Created by silvman on 30.04.18.
//

#include <iostream>
#include "Client.h"
#include "Server.h"

mp::Client::Client(const std::string &ip, unsigned short port) : connected_(false) {
    std::cout << msg::waiting_connection << std::endl;
    if (socket_.connect(ip, port) == sf::Socket::Status::Done) {
        connected_ = true;
    };
    selector_.add(socket_);

    std::cout << msg::connected << std::endl;
}

bool mp::Client::askEvents() {
    if (selector_.wait(constants::waitTime())) { // TODO приемлимое время ожидания?
        sf::Packet packet;
        if (socket_.receive(packet) == sf::Socket::Done) {
            //  парсинг пакета на отдельные эвенты
            std::string data = (char *)packet.getData();
            parseEventString(data, incoming);

            for (auto &&event : incoming) {
                std::cout << "[get event] " << event.type << " " << event.value << std::endl;
            }

            return true;
        } else {
            throw std::logic_error(msg::error_accepting_events);
        }
    }

    return false;
}

bool mp::Client::sendEvents() {
    if (outcoming.empty())
        return false;

    sf::Packet packet;
    std::string message;
    encodeEventsToString(message, outcoming);


//    for (auto &&event : outcoming) {
//        std::cout << "[out event] " << event.type << " " << event.value << std::endl;
//    }

    std::cout << message << std::endl;
    packet.append(message.c_str(), message.size() + 1);

    if (socket_.send(packet) == sf::Socket::Done) {
        outcoming.clear();
        return true;
    } else {
        throw std::logic_error(msg::error_sending_events);
    }
}

bool mp::Client::isConnected() {
    return connected_;
}

