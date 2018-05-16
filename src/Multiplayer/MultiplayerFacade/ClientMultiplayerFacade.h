//
// Created by silvman on 16.05.18.
//

#ifndef SERVER_CLIENTMULTIPLAYERFACADE_H
#define SERVER_CLIENTMULTIPLAYERFACADE_H

#include "AbstractMultiplayerFacade.h"

namespace mp {
    class ClientMultiplayerFacade : public AbstractMultiplayerFacade {
    public:
        ClientMultiplayerFacade();

        bool isConnected() override;
        void connect() override ;

        bool askEvents() override;
        bool sendEvents() override;
    };
}



#endif //SERVER_CLIENTMULTIPLAYERFACADE_H
