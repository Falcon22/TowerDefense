//
// Created by silvman on 30.04.18.
//

#include <iostream>
#include "Client.h"
#include "Server.h"

mp::Client::Client(const std::string &ip, unsigned short port) {
    std::cout << msg::waiting_connection << std::endl;
    socket_.connect(ip, port);
    selector_.add(socket_);

    // pending ID
    while (true) {
        if (selector_.wait(constants::waitTime())) {
            if(selector_.isReady(socket_)) {
                sf::Packet packet;
                if (socket_.receive(packet) == sf::Socket::Done) {
                    std::string id_str = (char *)packet.getData();
                    player_id_ = atoi(id_str.c_str());

                    std::cout << "my id is " << player_id_ << std::endl;
                    break;

                } else {
                    std::cout << "error"<< std::endl;
                }
            }
        }
    }

    if (player_id_ == 1) {
        while (true) {
            if (selector_.wait(constants::waitTime())) {
                if(selector_.isReady(socket_)) {
                    sf::Packet packet;
                    if (socket_.receive(packet) == sf::Socket::Done) {
                        std::string id_str = (char *)packet.getData();
                        if (atoi(id_str.c_str()) == 2) {
                            std::cout << "start game" << std::endl;
                            break;
                        }
                    } else {
                        std::cout << "error" << std::endl;
                    }
                }
            }
        }
    }
}

bool mp::Client::askEvents() {
    if (selector_.wait(constants::waitTime())) { // TODO приемлимое время ожидания?
        sf::Packet packet;
        if (socket_.receive(packet) == sf::Socket::Done) {
            //  парсинг пакета на отдельные эвенты
            std::string data = (char *)packet.getData();
            auto iterator = data.begin();

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

                incoming.emplace_back(sId, sType, sValue, sTime);
            }

            for (auto &&item : incoming) {
                std::cout << item.id << " " << item.type << " " << item.value << " " << item.time.asMicroseconds() << std::endl;
            }

            incoming.clear();

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

    message.append(std::to_string(outcoming.size()) + " ");

    //  сборка сообщения, включающего все эвенты
    for (auto &&e : outcoming) {
        message.append(std::to_string(e.id) + " " + e.type + " " + e.value + " " + std::to_string(e.time.asMicroseconds()) + " ");
    }

    std::cout << message << std::endl;
    packet.append(message.c_str(), message.size());

    if (socket_.send(packet) == sf::Socket::Done) {
        outcoming.clear();
        return true;
    } else {
        throw std::logic_error(msg::error_sending_events);
    }
}
