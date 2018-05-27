//
// Created by silvman on 16.05.18.
//

#include <iostream>
#include "ClientMultiplayerFacade.h"
#include "../ConnectionFacade/ClientConnectionFacade.h"

bool mp::ClientMultiplayerFacade::askEvents() {
    if (connection->hasNewData()) try {
            connection->getData(incoming);
            return true;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }

    return false;
}

bool mp::ClientMultiplayerFacade::sendEvents() {
    if (!outcoming.empty()) try {
            connection->sendData(outcoming);
            return true;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }

    return false;
}

void mp::ClientMultiplayerFacade::connect() {
    connection->connect();

}

bool mp::ClientMultiplayerFacade::isConnected() {
    return connection->isConnected();
}

mp::ClientMultiplayerFacade::ClientMultiplayerFacade() {
    connection = std::unique_ptr<AbstractConnectionFacade>(new ClientConnectionFacade);
}
