//
// Created by silvman on 08.04.18.
//

#ifndef TOWERDEFENSE_PLAYER_HPP
#define TOWERDEFENSE_PLAYER_HPP

#include <SFML/Network.hpp>

namespace server {
    class event {
        // placeholder
    public:
        void execute();
    };


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
        bool connected;

    public:
        player();
        explicit player(int id = 0);
        ~player();


        sf::TcpSocket& getSocket();
        event getNewEvent();

        void disconnect();
        void reconnect();
        bool isConnected() const;
    };

    class game : public entity {
    private:
        player player_one;
        player player_second;
        std::vector<event> events;

    public:
        player &getPlayerOne();
        player &getPlayerSecond();

        void addEvent(const event& event);
        std::vector<event>& getEvents();

    };
}

#endif //TOWERDEFENSE_PLAYER_HPP
