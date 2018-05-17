//
// Created by silvman on 16.05.18.
//

#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include <SFML/Network.hpp>
#include "Entity.h"
#include "Event.h"

namespace mp {
    class player : public entity {
    public:
        enum connection_state {
            notConnected = 0,
            connected,
            notAvailable
        };

        explicit player(int id = 0);
        ~player() override;

        sf::TcpSocket& getSocket();


        void getEvents();
        void sendEvents();
//        void resendEvents(player& to_who);

        // вызывается у первого игрока для уведомления о начале игры
        bool hasNewData(sf::SocketSelector &selector);

        void disconnect();

        void connect(sf::TcpListener &listener, sf::SocketSelector &selector);

        void startGame();

        bool isAvailable() const;
        bool isConnected() const;

        bool isInGame() const;
        void setInGame();


        std::vector<mp::Event> from_client;
        std::vector<mp::Event> to_send;


    private:
        struct msg {
            static constexpr const char *get_events = "[player:success] get events from ";
            static constexpr const char *not_get_events = "[player:error] can't recieve events";
            static constexpr const char *send_id = "[player:success] send id to ";
            static constexpr const char *not_send_id = "[player:error] send id to";
            static constexpr const char *connect_player = "[player:success] connected player " ;
            static constexpr const char *not_connect_player = "[player:error] didn't connect player" ;
            static constexpr const char *send_events = "[player:success] send events to " ;
            static constexpr const char *not_send_events = "[player:error] can't send events to " ;
        };

        sf::TcpSocket       socket_;
        connection_state    state_;
        bool                in_game_;
    };

}




#endif //SERVER_PLAYER_H
