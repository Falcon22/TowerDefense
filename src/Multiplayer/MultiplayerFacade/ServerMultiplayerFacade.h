//
// Created by silvman on 16.05.18.
//

#ifndef SERVER_SERVERMULTIPLAYERFACADE_H
#define SERVER_SERVERMULTIPLAYERFACADE_H

#include "AbstractMultiplayerFacade.h"
#include "../Entities/Player.h"

namespace mp {
    class ServerMultiplayerFacade : public AbstractMultiplayerFacade {
    public:
        ServerMultiplayerFacade(mp::player& first, mp::player& second);

        bool isConnected() override;
        void connect() override ;

        bool askEvents() override;
        bool sendEvents() override;

    };
}



#endif //SERVER_SERVERMULTIPLAYERFACADE_H
