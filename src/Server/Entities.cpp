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




mp::player::player() : state_(notConnected) { }

mp::player::player(int id)
        : entity(id), state_(notConnected) { }


void mp::player::disconnect() {
    state_ = notConnected;
}

void mp::player::reconnect() {
    state_ = connected; // TODO не так просто
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
        std::cout << "[success] get events from " << getId() << '\n';
        std::string data = (char *)packet.getData();

        parseEventString(data, from_client);
    } else {
        throw std::logic_error("[fail] can't recieve events");
    }
} catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    state_ = notAvailable;
    throw;
}

void mp::player::connect(sf::TcpListener &listener, sf::SocketSelector &selector) try {
    if (listener.accept(socket_) == sf::Socket::Done) {
        selector.add(socket_);
        state_ = connected; // помечает, что подключено

        std::cout << "[success] connected player " << id << std::endl;

        sf::Packet packet_id;
        
        
        std::string str_id(std::to_string(id));
        packet_id.append(str_id.c_str(), str_id.size() + 1);

        std::cout << "id " << id << " is " << (char *)packet_id.getData() << std::endl;

        if (socket_.send(packet_id) == sf::Socket::Done) {
            std::cout << "[success] send id to " << id << std::endl;
        } else {
            std::cout << "[error] send " << id << std::endl;
        }

    } else {
        throw std::logic_error("[fail] didn't connect player");
    }
} catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    state_ = notAvailable;
}

void mp::player::getReady() try {
    sf::Packet packet;
    std::string msg("2");
    packet.append(msg.c_str(), msg.size());
    if (socket_.send(packet) == sf::Socket::Done) {
        std::cout << "[success] send id 2 to " << id << std::endl;
    } else {
        throw std::logic_error("[error] send id 2 to " + id);
    }
} catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    state_ = notAvailable;
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

    packet.append(sEvents.c_str(), sEvents.size());
    if (socket_.send(packet) == sf::Socket::Done) { // блокирующий вызов, может стать причиной медленной пересылки эвентов
        to_send.clear();
        std::cout << "[success] send events to " << id << std::endl;
    } else {
        throw std::logic_error("[error] send events to " + id);
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


//mp::player& mp::game::getPlayerOne() {
//    return player_one;
//}
//
//mp::player& mp::game::getPlayerSecond() {
//    return player_second;
//}
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

        for (; *iterator != ' '; ++iterator)
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
