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
    sf::Packet packet_id;

    std::string str_id(std::to_string(id));
    packet_id.append(str_id.c_str(), str_id.size() + 1);

    if (socket_.send(packet_id) == sf::Socket::Done) {
        std::cout << msg::send_id << id << std::endl;
    } else {
        std::cout << msg::not_send_id << id << std::endl;
    }
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

bool mp::game::isReady() const {
    return (first_connected_ && second_connected_);
}

void mp::game::join(int player_id) {
    if (is_started_)
        throw std::logic_error(msg::game_running);

    if (!first_connected_) {
        player_id_first_ = player_id;
        first_connected_ = true;
    } else if (!second_connected_) {
        player_id_second_ = player_id;
        second_connected_ = true;
    }
}

const std::string &mp::game::getName() const {
    return name_;
}

mp::game::game(const std::string &name) :
        name_(name),
        is_started_(false),
        first_connected_(false),
        second_connected_(false),
        player_id_second_(0),
        player_id_first_(0)
{ }

bool mp::game::isStarted() const {
    return is_started_;
}

void mp::game::start() {
    is_started_ = true;
}

int mp::game::getFirstId() const {
    return player_id_first_;
}

int mp::game::getSecondId() const {
    return player_id_second_;
}
