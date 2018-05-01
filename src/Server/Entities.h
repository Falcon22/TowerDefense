//
// Created by silvman on 08.04.18.
//

#ifndef TOWERDEFENSE_PLAYER_HPP
#define TOWERDEFENSE_PLAYER_HPP

#include <SFML/Network.hpp>

namespace mp {

    struct Event {
        int         id;
        char        type;
        std::string value;
        sf::Time    time;

        Event(int id, char type, const std::string &value, sf::Time time);
        Event(const std::string &sId, const std::string &sType, const std::string &value, const std::string &sTime);
    };

    void parseEventString(const std::string& sEvents, std::vector<mp::Event>& vEvents);
    void encodeEventsToString(std::string& sEvents, std::vector<mp::Event>& vEvents);

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
    public:
        enum player_state {
            notConnected = 0,
            connected,
            notAvailable
        };

        player();
        explicit player(int id = 0);
        ~player();

        sf::TcpSocket& getSocket();


        void getEvents();
        void sendEvents();
//        void resendEvents(player& to_who);

        void getReady(); // вызывается у первого игрока для уведомления о начале игры
        bool hasNewData(sf::SocketSelector &selector);

        void disconnect();
        void reconnect();

        void connect(sf::TcpListener &listener, sf::SocketSelector &selector);

        bool isAvailable() const;
        bool isConnected() const;

        std::vector<mp::Event> from_client;
        std::vector<mp::Event> to_send;


    private:
        sf::TcpSocket socket_;
        player_state state_;
    };

//    class game : public entity {
//    private:
//        player player_one;
//        player player_second;
//        std::vector<event> events;
//
//    public:
//        player &getPlayerOne();
//        player &getPlayerSecond();
//
//        void addEvent(const event& event);
//        std::vector<event>& getEvents();
//
//    };
}

#endif //TOWERDEFENSE_PLAYER_HPP
