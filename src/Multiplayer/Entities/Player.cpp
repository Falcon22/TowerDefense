//
// Created by silvman on 16.05.18.
//

#include <iostream>
#include "Player.h"

mp::player::player(int id)
        : entity(id), state_(notConnected) { }


void mp::player::disconnect() {
    state_ = notConnected;
}

mp::player::~player() {
    socket_.disconnect();
}

bool mp::player::isAvailable() const {
    return state_ != notAvailable;
}

void mp::player::getEvents() try {
    sf::Packet packet;
    if (socket_.receive(packet) == sf::Socket::Done) {
        std::cout << msg::get_events << id << std::endl;
        std::string data = (char *)packet.getData();

        parseEventString(data, from_client);
    } else {
        throw std::logic_error(msg::not_get_events);
    }
} catch (const std::exception& e) {
    state_ = notAvailable;
    throw;
}

void mp::player::startGame() {
    to_send.emplace_back(0, 'j', std::to_string(id), sf::microseconds(0));
    sendEvents();
}


void mp::player::connect(sf::TcpListener &listener, sf::SocketSelector &selector) try {
    if (listener.accept(socket_) == sf::Socket::Done) {
        selector.add(socket_);
        state_ = connected; // помечает, что подключено

        std::cout << msg::connect_player << id << std::endl;

    } else {
        throw std::logic_error(msg::not_connect_player);
    }
} catch (const std::exception& e) {
    state_ = notAvailable;
    throw;
}

bool mp::player::hasNewData(sf::SocketSelector &selector) {
    return selector.isReady(socket_);
}

void mp::player::sendEvents() try {
    if (to_send.empty())
        return;

    sf::Packet packet;

    std::string sEvents;
    encodeEventsToString(sEvents, to_send);

    packet.append(sEvents.c_str(), sEvents.size() + 1);
    if (socket_.send(packet) == sf::Socket::Done) { // блокирующий вызов, может стать причиной медленной пересылки эвентов
        for (auto &&send : to_send) {
            std::cout << send.id << " " << send.value << std::endl;
        }
        to_send.clear();
        std::cout << msg::send_events << id << std::endl;
    } else {
        throw std::logic_error(msg::not_send_events + id);
    }

} catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    state_ = notAvailable;
}

bool mp::player::isConnected() const {
    return state_ == connected;
}

sf::TcpSocket &mp::player::getSocket() {
    return socket_;
}

bool mp::player::isInGame() const {
    return in_game_;
}

void mp::player::setInGame() {
    in_game_ = true;
}