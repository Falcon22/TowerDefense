//
// Created by silvman on 08.04.18.
//

#include <iostream>
#include "Server.h"

/*

mp::worker::worker(unsigned short port): running(true) {
    listener.listen(port);
    selector.add(listener);
}

mp::worker::~worker() {
    listener.close(); // TODO Нужно?
}

void mp::worker::work() {
    std::cout << "[run]" << '\n';
    while (running) {
        if (selector.wait(constants::waitTime())) {
            if (selector.isReady(listener)) {
                tryNewConnection();
            } else {
                recievePlayerEvents();
                recieveGamesEvents();
            }
        } else {
            proceedEvents();
            proceedGames();
            sendPlayerEvents();
            sendGamesEvents();
        }
    }
}

void mp::worker::tryNewConnection() {
    player& new_player = pool_players.create();
    if (listener.accept(new_player.getSocket()) == sf::Socket::Done) {
        selector.add(new_player.getSocket());
        std::cout << "[success] connected player " << new_player.getId() << '\n';
    } else {
        std::cout << "[fail] didn't connect player" << '\n';
        pool_players.remove(new_player.getId());
    }
}

void mp::worker::recievePlayerEvents() {
    auto& players = pool_players.getEntities();
    for (auto &&player : players) {
        try {
            if(player.isConnected() && selector.isReady(player.getSocket())) {
                event new_events = player.getEvents(<#initializer#>);
                // TODO вероятно будем передавать контейнер эвентов, нужно будет поменять
                players_input_events.push_back(new_events);
            }

        } catch (const std::exception& e) {
            std::cout << e.what() << '\n';
            player.disconnect();
        }
    }
}

void mp::worker::recieveGamesEvents() {
    auto& games = pool_games.getEntities();
    for (auto &&game : games) {
        auto& one = game.getPlayerOne();
        auto& sec = game.getPlayerSecond();

        event one_events, sec_events;

        try {
            if(one.isConnected() && selector.isReady(one.getSocket())) {
                one_events = one.getEvents(<#initializer#>);
                game.addEvent(one_events);
            }

        } catch (const std::exception& e) {
            std::cout << e.what() << '\n';
            one.disconnect();
        }

        try {
            if(sec.isAvailable() && selector.isReady(sec.getSocket())) {
                sec_events = sec.getEvents(<#initializer#>);
                game.addEvent(sec_events);
            }

        } catch (const std::exception& e) {
            std::cout << e.what() << '\n';
            sec.disconnect();
        }
    }

}

void mp::worker::proceedEvents() {
    for (auto &&item : players_input_events) {
        // TODO
        event ready_event;
        players_output_events.push_back(ready_event);
    }
}

void mp::worker::proceedGames() {
    // TODO Under construction
}

void mp::worker::sendPlayerEvents() {
    for (auto &&outputEvent : players_output_events) {
//        outputEvent.execute();
    }
}

void mp::worker::sendGamesEvents() {
    // placeholder
}


*/

mp::simple_worker::simple_worker(unsigned short port) : first_(1), second_(2) {
    while (listener_.listen(port) != sf::Socket::Status::Done);

    selector_.add(listener_);

}

void mp::simple_worker::work() {
    std::cout << "[run] simple server" << '\n';

    while (running_) {
        if (!first_.isAvailable() && !second_.isAvailable())
            running_ = false;
        
        if (selector_.wait(constants::waitTime())) {
            if (selector_.isReady(listener_)) {
                if (!first_.isConnected()) {
                    first_.connect(listener_, selector_);
                } else {
                    second_.connect(listener_, selector_);
                    first_.getReady();
                }
            } else {
                if (first_.hasNewData(selector_)) {
                    try {
                        first_.getEvents();
                    } catch (const std::exception& e) {
                        selector_.remove(first_.getSocket());
                    }
                }

                if (second_.hasNewData(selector_)) {
                    try {
                        second_.getEvents();
                    } catch (const std::exception& e) {
                        selector_.remove(second_.getSocket());
                    }
                }
            }
        } else {
            // TODO validation:
            // здесь происходит вызов Game.servRun(player &first, player &second);



            first_.to_send = second_.from_client;
            if (!second_.isAvailable())
                first_.to_send.emplace_back(0, 's', "stop", sf::microseconds(0)); // системный вызов, завершающий игру

            second_.from_client.clear(); // в Game этот вектор после обработки должен быть очищен!


            second_.to_send = first_.from_client;
            if (!first_.isAvailable())
                second_.to_send.emplace_back(0, 's', "stop", sf::microseconds(0)); // системный вызов, завершающий игру

            first_.from_client.clear(); // в Game этот вектор после обработки должен быть очищен!


            first_.sendEvents();
            second_.sendEvents();
        }
    }
}
