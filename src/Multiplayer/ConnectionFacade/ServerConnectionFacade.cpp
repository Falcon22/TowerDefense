//
// Created by silvman on 16.05.18.
//

#include "ServerConnectionFacade.h"
#include "../Constants.h"

bool mp::ServerConnectionFacade::hasNewData() {
    if (selector_.wait(constants::waitTime()))
        return first_.hasNewData(selector_) || second_.hasNewData(selector_);

    return false;
}

void mp::ServerConnectionFacade::getData(std::vector<mp::Event> &to) {
    if (first_.hasNewData(selector_)) {
        try {
            first_.getEvents();
            to.insert(to.end(), first_.from_client.begin(), first_.from_client.end()); // сращиваем 2 вектора
            first_.from_client.clear(); // очищаем после получения данных
        } catch (const std::exception &e) {
            selector_.remove(first_.getSocket());
        }
    }

    if (second_.hasNewData(selector_)) {
        try {
            second_.getEvents();
            to.insert(to.end(), second_.from_client.begin(), second_.from_client.end()); // сращиваем 2 вектора
            second_.from_client.clear(); // очищаем после получения данных
        } catch (const std::exception &e) {
            selector_.remove(second_.getSocket());
        }
    }
}

void mp::ServerConnectionFacade::sendData(std::vector<mp::Event> &from) {
    for (auto &&event : from) {
        switch (event.id) {
            case 1: {
                second_.to_send.push_back(event);
                break;
            }

            case 2: {
                first_.to_send.push_back(event);
                break;
            }

            case 0: { // broadcasting
                second_.to_send.push_back(event);
                first_.to_send.push_back(event);

                break;
            }

            default:
                break;
        }
    }

    first_.sendEvents();
    second_.sendEvents();

    from.clear(); // TODO нужна проверка на отправленность
}

void mp::ServerConnectionFacade::connect() {
    // does nothing as the connection comes from the master process
}

bool mp::ServerConnectionFacade::isConnected() {
    return first_.isAvailable() && second_.isAvailable(); // грубая проверка подключения с обоими игроками
}
