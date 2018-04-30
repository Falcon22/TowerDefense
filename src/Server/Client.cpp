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
            std::string other_player_id = std::to_string(data[0]);
            std::string str_num_events;

            int j;
            for(j = 0; data[j] != ' '; j++)
                str_num_events += data[j];
            j++;

            int num_events = atoi(str_num_events.c_str());

            int read_events = 0;
            while (read_events != num_events) {
                std::string current_event;
                bool got_event = false;
                int read_fields = 0;
                while(!got_event) {
                    current_event += data[j++];
                    if (data[j] == ' ') {
                        read_fields++;
                        if (read_fields == 3) {
                            got_event = true;
                            read_fields = 0;
                            read_events++;
                            j++;
                        }
                    }
                }
                incoming.push_back(current_event);
            }

            return true;
        } else {
            throw std::logic_error(msg::error_receiving_events);
        }
    }

    return false;
}

bool mp::Client::sendEvents() {
    sf::Packet packet;
    std::string message;

    message.append(std::to_string(player_id_) + " " + std::to_string(outcoming.size()));

    //  сборка сообщения, включающего все эвенты
    for (auto &&e : outcoming) {
        message.append(e + " ");
    }

    packet.append(message.c_str(), message.size());

    if (socket_.send(packet) == sf::Socket::Done)
        return true;
    else
        throw std::logic_error(msg::error_sending_events);
}
