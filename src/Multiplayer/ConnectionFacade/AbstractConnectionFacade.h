//
// Created by silvman on 16.05.18.
//

#ifndef SERVER_ABSTRACTCONNECTIONFACADE_H
#define SERVER_ABSTRACTCONNECTIONFACADE_H


#include "../Entities/Event.h"

namespace mp {
    class AbstractConnectionFacade {
    public:
        virtual void connect() = 0;
        virtual bool hasNewData() = 0;
        virtual bool isConnected() = 0;
        virtual void getData(std::vector<mp::Event> &to) = 0;
        virtual void sendData(std::vector<mp::Event>& from) = 0;

        virtual ~AbstractConnectionFacade();
    };
}


#endif //SERVER_ABSTRACTCONNECTIONFACADE_H
