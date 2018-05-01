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

std::string mp::player::getEvents(sf::SocketSelector &selector) {
    sf::Packet packet;
    if (socket.receive(packet) == sf::Socket::Done) {
        std::cout << "[success] get event from " << getId() << '\n';
        return (char *)packet.getData();
    } else {
        throw std::logic_error("[fail] can't recieve event");
    }
}

void mp::player::connect(sf::TcpListener &listener, sf::SocketSelector &selector) {
    if (listener.accept(socket) == sf::Socket::Done) {
        selector.add(socket);
        connected = true; // помечает, что подключено

        std::cout << "[success] connected player " << id << std::endl;

        sf::Packet packet_id;
        
        
        std::string str_id(std::to_string(id));
        packet_id.append(str_id.c_str(), str_id.size() + 1);

        std::cout << "id " << id << " is " << (char *)packet_id.getData() << std::endl;

        if (socket.send(packet_id) == sf::Socket::Done) {
            std::cout << "[success] send id to " << id << std::endl;
        } else {
            std::cout << "[error] send " << id << std::endl;
        }

    } else {
        std::cout << "[fail] didn't connect player" << '\n';
    }
}

void mp::player::getReady() {
    sf::Packet packet;
    std::string msg("2");
    packet.append(msg.c_str(), msg.size());
    if (socket.send(packet) == sf::Socket::Done) {
        std::cout << "[success] send id 2 to " << id << std::endl;
    } else {
        std::cout << "[error] send id 2 to " << id << std::endl;
    }
}

bool mp::player::isReady(sf::SocketSelector &selector) {
    return selector.isReady(socket);
}

void mp::player::sendEvents(const std::string &events) {
    sf::Packet packet;

    packet.append(events.c_str(), events.size());
    if (socket.send(packet) == sf::Socket::Done) { // блокирующий вызов, может стать причиной медленной пересылки эвентов
        std::cout << "[success] send events to " << id << std::endl;
    } else {
        std::cout << "[error] send events to " << id << std::endl;
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
