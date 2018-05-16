//
// Created by silvman on 30.04.18.
//

#ifndef TOWERDEFENSE_CLIENT_H
#define TOWERDEFENSE_CLIENT_H

#include <SFML/Network.hpp>
#include <utility>
#include "Entities.h"


namespace mp {
//    class AbstractConnectionFacade {
//    public:
//        virtual void connect() = 0;
//        virtual bool hasNewData() = 0;
//        virtual bool isConnected() = 0;
//        virtual void getData(std::vector<mp::Event> &to) = 0;
//        virtual void sendData(std::vector<mp::Event>& from) = 0;
//
//        virtual ~AbstractConnectionFacade();
//    };

//    class ClientConnectionFacade : public AbstractConnectionFacade {
//    private:
//        struct msg {
//            static constexpr const char *waiting_connection = "[client:process] connecting to server";
//            static constexpr const char *error_sending_events = "[client:fail] server didn't accept events";
//            static constexpr const char *error_accepting_events = "[client:fail] can't accept events";
//            static constexpr const char *connected = "[client:success] connected to server";
//        };
//
//        sf::TcpSocket       socket_;
//        sf::SocketSelector  selector_;
//        bool                connected_ = false;
//
//    public:
//        void connect() override;
//        bool hasNewData() override;
//        bool isConnected() override;
//
//        /*
//         * Эти два метода кидаются исключениями std::logic_error в случаях,
//         * когда с соединением что-то не так
//         */
//        void getData(std::vector<mp::Event> &to) override;
//        void sendData(std::vector<mp::Event> &from) override;
//
//    };

//    class ServerConnectionFacade : public AbstractConnectionFacade {
//    private:
//        mp::player& first_;
//        mp::player& second_;
//        sf::SocketSelector selector_;
//
//    public:
//        explicit ServerConnectionFacade(mp::player &first, mp::player &second) : first_(first), second_(second) {
//            selector_.add(first_.getSocket());
//            selector_.add(second_.getSocket());
//        };
//
//        bool isConnected() override;
//        void connect() override;
//        bool hasNewData() override;
//        void getData(std::vector<mp::Event> &to) override;
//        void sendData(std::vector<mp::Event> &from) override;
//    };



    class AbstractMultiplayerFacade {
    protected:
        std::unique_ptr<mp::AbstractConnectionFacade> connection{};

    public:
        virtual ~AbstractMultiplayerFacade();

        virtual bool isConnected() = 0;
        virtual void connect() = 0;

        virtual bool askEvents() = 0;
        virtual bool sendEvents() = 0;

        std::vector<mp::Event> incoming{};
        std::vector<mp::Event> outcoming{};
    };

    class ClientMultiplayerFacade : public AbstractMultiplayerFacade {
    public:
        ClientMultiplayerFacade();

        bool isConnected() override;
        void connect() override ;

        bool askEvents() override;
        bool sendEvents() override;
    };

    class ServerMultiplayerFacade : public AbstractMultiplayerFacade {
    public:
        ServerMultiplayerFacade(mp::player& first, mp::player& second);

        bool isConnected() override;
        void connect() override ;

        bool askEvents() override;
        bool sendEvents() override;

    };

}


#endif //TOWERDEFENSE_CLIENT_H
