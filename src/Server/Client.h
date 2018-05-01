//
// Created by silvman on 30.04.18.
//

#ifndef TOWERDEFENSE_CLIENT_H
#define TOWERDEFENSE_CLIENT_H

#include <SFML/Network.hpp>
#include <utility>


namespace mp {
    struct Event {
        int         id;
        char        type;
        std::string value;
        sf::Time    time;

        Event(int id, char type, const std::string &value, sf::Time time) :
                id(id),
                type(type),
                value(value),
                time(time) { }

        Event(const std::string &sId, const std::string &sType, const std::string &value, const std::string &sTime) :
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
    };

    class Client {
    private:
        struct msg {
            static constexpr const char *waiting_connection = "[process] connecting to server";
            static constexpr const char *error_sending_events = "[fail] server didn't accept events";
            static constexpr const char *error_accepting_events = "[fail] can't accept events";
        };

        sf::TcpSocket       socket_;
        sf::SocketSelector  selector_;
        int                 player_id_;

    public:
        explicit Client(const std::string &ip, unsigned short port = 55001);


        /*
         * Эти два метода кидаются исключениями std::logic_error в случаях,
         * когда с соединением что-то не так
         */
        bool askEvents();
        bool sendEvents();

        // эвенты
        std::vector<mp::Event> incoming;
        std::vector<mp::Event> outcoming;

    };

}


#endif //TOWERDEFENSE_CLIENT_H
