//
// Created by silvman on 08.04.18.
//

#include <SFML/Network.hpp>
#include <iostream>

int main () {
    sf::TcpSocket socket;
    unsigned short port;
    std::cin >> port;

    socket.connect("0.0.0.0", port);

    std::cout << "[connected]" << std::endl;
    std::string string_buf;

    while (std::cin >> string_buf) {
        sf::Packet packet;
        packet.append(string_buf.c_str(), string_buf.length() + 1);
        socket.send(packet);
    }

    return 0;
}