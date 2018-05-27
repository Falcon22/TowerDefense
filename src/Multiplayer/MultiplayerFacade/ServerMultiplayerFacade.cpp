//
// Created by silvman on 16.05.18.
//

#include <iostream>
#include "ServerMultiplayerFacade.h"
#include "../ConnectionFacade/ServerConnectionFacade.h"

mp::ServerMultiplayerFacade::ServerMultiplayerFacade(mp::player &first, mp::player &second) {
    connection = std::unique_ptr<AbstractConnectionFacade>(new mp::ServerConnectionFacade(first, second));
}

bool mp::ServerMultiplayerFacade::askEvents() {
    if (connection->hasNewData()) try {
            connection->getData(incoming);
            return true;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }

    return false;
}

bool mp::ServerMultiplayerFacade::sendEvents() {
    if (!outcoming.empty()) try {
            connection->sendData(outcoming);
            return true;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }

    return false;
}

void mp::ServerMultiplayerFacade::connect() {
    connection->connect();
}

bool mp::ServerMultiplayerFacade::isConnected() {
    return connection->isConnected();
}

