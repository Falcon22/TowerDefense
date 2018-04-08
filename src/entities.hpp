//
// Created by silvman on 08.04.18.
//

#ifndef TOWERDEFENSE_PLAYER_HPP
#define TOWERDEFENSE_PLAYER_HPP

#include <SFML/Network.hpp>

namespace server {
    class entity {
    protected:
        int id;

    public:
        explicit entity(int id = 0);
        virtual ~entity() = default;

        int getId() const;
        void setId(int id);
    };


    class player : public entity {
    private:
        sf::TcpSocket socket;
        bool isConnected;

    public:
        player() = default;
        explicit player(sf::TcpSocket&& socket, int id = 0);
        ~player();


        sf::TcpSocket& getSocket() const;

        void disconnect();
        void reconnect();
    };


    class game : public entity {
    private:
        player player_one;
        player player_second;

    public:
    };
}

#endif //TOWERDEFENSE_PLAYER_HPP
