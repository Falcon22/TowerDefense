//
// Created by silvman on 16.05.18.
//

#ifndef SERVER_CLIENTCONNECTIONFACADE_H
#define SERVER_CLIENTCONNECTIONFACADE_H

#include "AbstractConnectionFacade.h"

namespace mp {
    class ClientConnectionFacade : public AbstractConnectionFacade {
    private:
        struct msg {
            static constexpr const char *waiting_connection = "[client:process] connecting to server";
            static constexpr const char *error_sending_events = "[client:fail] server didn't accept events";
            static constexpr const char *error_accepting_events = "[client:fail] can't accept events";
            static constexpr const char *connected = "[client:success] connected to server";
        };

        sf::TcpSocket       socket_;
        sf::SocketSelector  selector_;
        bool                connected_ = false;

    public:
        void connect() override;
        bool hasNewData() override;
        bool isConnected() override;

        /*
         * Эти два метода кидаются исключениями std::logic_error в случаях,
         * когда с соединением что-то не так
         */
        void getData(std::vector<mp::Event> &to) override;
        void sendData(std::vector<mp::Event> &from) override;

    };
}


#endif //SERVER_CLIENTCONNECTIONFACADE_H
