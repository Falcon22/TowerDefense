//
// Created by silvman on 08.04.18.
//

#include "entities.hpp"


int server::entity::getId() const {
    return id;
}

void server::entity::setId(int id) {
    entity::id = id;
}

server::entity::entity(int id = 0): id(id) { }


server::player::player(sf::TcpSocket &&socket, int id = 0)
        : socket(std::move(socket)), entity(id), isConnected(true) { }

sf::TcpSocket& server::player::getSocket() const {
    return socket;
}

void server::player::disconnect() {
    isConnected = false;
}

void server::player::reconnect() {
    isConnected = true; // TODO не так просто
}

server::player::~player() {
    socket.disconnect();
}
