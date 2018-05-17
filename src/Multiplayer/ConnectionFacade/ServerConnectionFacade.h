//
// Created by silvman on 16.05.18.
//

#ifndef SERVER_SERVERCONNECTIONFACADE_H
#define SERVER_SERVERCONNECTIONFACADE_H

#include "../Entities/Player.h"
#include "AbstractConnectionFacade.h"

namespace mp {
    class ServerConnectionFacade : public AbstractConnectionFacade {
    private:
        mp::player& first_;
        mp::player& second_;
        sf::SocketSelector selector_;

    public:
        explicit ServerConnectionFacade(mp::player &first, mp::player &second) : first_(first), second_(second) {
            selector_.add(first_.getSocket());
            selector_.add(second_.getSocket());
        };

        bool isConnected() override;
        void connect() override;
        bool hasNewData() override;
        void getData(std::vector<mp::Event> &to) override;
        void sendData(std::vector<mp::Event> &from) override;
    };
}



#endif //SERVER_SERVERCONNECTIONFACADE_H
