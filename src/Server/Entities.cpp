//
// Created by silvman on 08.04.18.
//

#include <iostream>
#include "Entities.h"


int mp::entity::getId() const {
    return id;
}

void mp::entity::setId(int id) {
    entity::id = id;
}

mp::entity::entity(int id): id(id) { }


mp::player::player() : connected(true) { }

mp::player::player(int id)
        : entity(id), connected(false) { }

sf::TcpSocket& mp::player::getSocket() {
    return socket;
}

void mp::player::disconnect() {
    connected = false;
}

void mp::player::reconnect() {
    connected = true; // TODO не так просто
}

mp::player::~player() {
    socket.disconnect();
}

bool mp::player::isConnected() const {
    return connected;
}

mp::event mp::player::getNewEvent() {
    sf::Packet packet;
    if (socket.receive(packet) == sf::Socket::Done) {
        // TODO распарсить ответ
        std::cout << "[success] get event from " << getId() << '\n';
        return mp::event();
    } else {
        throw std::logic_error("[fail] can't recieve event");
    }
}

mp::player& mp::game::getPlayerOne() {
    return player_one;
}

mp::player& mp::game::getPlayerSecond() {
    return player_second;
}

void mp::game::addEvent(const mp::event &event) {
    events.push_back(event);
}

std::vector<mp::event> &mp::game::getEvents() {
    return events;
}

void mp::event::execute() {
    // placeholder
}
