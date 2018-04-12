//
// Created by silvman on 08.04.18.
//

#include <iostream>
#include "entities.hpp"


int server::entity::getId() const {
    return id;
}

void server::entity::setId(int id) {
    entity::id = id;
}

server::entity::entity(int id): id(id) { }


server::player::player() : connected(true) { }

server::player::player(int id)
        : entity(id), connected(true) { }

sf::TcpSocket& server::player::getSocket() {
    return socket;
}

void server::player::disconnect() {
    connected = false;
}

void server::player::reconnect() {
    connected = true; // TODO не так просто
}

server::player::~player() {
    socket.disconnect();
}

bool server::player::isConnected() const {
    return connected;
}

server::event server::player::getNewEvent() {
    sf::Packet packet;
    if (socket.receive(packet) == sf::Socket::Done) {
        // TODO распарсить ответ
        std::cout << "[success] get event from " << getId() << '\n';
        return server::event();
    } else {
        throw std::logic_error("[fail] can't recieve event");
    }
}

server::player& server::game::getPlayerOne() {
    return player_one;
}

server::player& server::game::getPlayerSecond() {
    return player_second;
}

void server::game::addEvent(const server::event &event) {
    events.push_back(event);
}

std::vector<server::event> &server::game::getEvents() {
    return events;
}

void server::event::execute() {
    // placeholder
}
