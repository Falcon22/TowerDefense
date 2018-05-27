//
// Created by silvman on 16.05.18.
//

#include <iostream>
#include "ClientConnectionFacade.h"
#include "../../GameConstants.h"

bool mp::ClientConnectionFacade::hasNewData() {
    if(selector_.wait(sf::milliseconds(GameConstants::instance().cSELECTOR_WAIT_TIME())))
        return selector_.isReady(socket_);

    return false;
}

void mp::ClientConnectionFacade::getData(std::vector<mp::Event> &to) {
    sf::Packet packet;
    if (socket_.receive(packet) == sf::Socket::Done) {
        //  парсинг пакета на отдельные эвенты
        std::string data = (char *)packet.getData();
        parseEventString(data, to);

        if (GameConstants::instance().cDEBUG_MODE()) for (auto &&event : to)
                std::cout << "[get event] " << event.type << " " << event.value << std::endl;

    } else {
        throw std::logic_error(msg::error_accepting_events);
    }
}

void mp::ClientConnectionFacade::sendData(std::vector<mp::Event> &from) {
    sf::Packet packet;
    std::string message;
    encodeEventsToString(message, from);

    if (GameConstants::instance().cDEBUG_MODE()) for (auto &&event : from) {
            std::cout << "[out event] " << event.type << " " << event.value << std::endl;
        }

    std::cout << message << std::endl;
    packet.append(message.c_str(), message.size() + 1);

    if (socket_.send(packet) == sf::Socket::Done) {
        from.clear();
    } else {
        throw std::logic_error(msg::error_sending_events);
    }
}

void mp::ClientConnectionFacade::connect() {
    std::cout << msg::waiting_connection << std::endl;
    if (socket_.connect(GameConstants::instance().cIP_ADDR_SERVER(),
                        (unsigned short)GameConstants::instance().cCONNECTION_PORT()) == sf::Socket::Status::Done) {
        connected_ = true;
        selector_.add(socket_);
        std::cout << msg::connected << std::endl;
    }
}

bool mp::ClientConnectionFacade::isConnected() {
    return connected_;
}