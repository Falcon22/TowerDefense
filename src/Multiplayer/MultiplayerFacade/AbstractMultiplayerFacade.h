//
// Created by silvman on 16.05.18.
//

#ifndef SERVER_MULTIPLAYERFACADE_H
#define SERVER_MULTIPLAYERFACADE_H

#include "../ConnectionFacade/AbstractConnectionFacade.h"

namespace mp {
    class AbstractMultiplayerFacade {
    protected:
        std::unique_ptr<mp::AbstractConnectionFacade> connection;

    public:
        virtual ~AbstractMultiplayerFacade();

        virtual bool isConnected() = 0;
        virtual void connect() = 0;

        virtual bool askEvents() = 0;
        virtual bool sendEvents() = 0;

        std::vector<mp::Event> incoming{};
        std::vector<mp::Event> outcoming{};
    };
}



#endif //SERVER_MULTIPLAYERFACADE_H
