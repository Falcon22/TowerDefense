//
// Created by silvman on 08.04.18.
//

#include <iostream>
#include "server.hpp"

server::worker::worker(unsigned short port): running(true) {
    listener.listen(port);
    selector.add(listener);
}

server::worker::~worker() {
    listener.close(); // TODO Нужно?
}

void server::worker::work() {
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

void server::worker::tryNewConnection() {
    // TODO Так не заработает, надо создавать в poolPlayers нового игрока, и затем брать у него сокет

    player& new_player = pool_players.create();
    if (listener.accept(new_player.getSocket()) == sf::Socket::Done) {
        selector.add(new_player.getSocket());
//        pool_players.add(std::move(new_player));
        std::cout << "[success] connected player" << '\n';
    } else {
        std::cout << "[fail] didn't connect player" << '\n';
    }
}

void server::worker::recievePlayerEvents() {
    auto& players = pool_players.getEntities();
    for (auto &&player : players) {
        try {
            if(player.isConnected() && selector.isReady(player.getSocket())) {
                event new_events = player.getNewEvent();
                // TODO вероятно будем передавать контейнер эвентов, нужно будет поменять
                players_input_events.push_back(new_events);
            }

        } catch (const std::exception& e) {
            std::cout << e.what() << '\n';
            player.disconnect();
        }
    }
}

void server::worker::recieveGamesEvents() {
    auto& games = pool_games.getEntities();
    for (auto &&game : games) {
        auto& one = game.getPlayerOne();
        auto& sec = game.getPlayerSecond();

        event one_events, sec_events;

        try {
            if(one.isConnected() && selector.isReady(one.getSocket())) {
                one_events = one.getNewEvent();
                game.addEvent(one_events);
            }

        } catch (const std::exception& e) {
            std::cout << e.what() << '\n';
            one.disconnect();
        }

        try {
            if(sec.isConnected() && selector.isReady(sec.getSocket())) {
                sec_events = sec.getNewEvent();
                game.addEvent(sec_events);
            }

        } catch (const std::exception& e) {
            std::cout << e.what() << '\n';
            sec.disconnect();
        }
    }

}

void server::worker::proceedEvents() {
    for (auto &&item : players_input_events) {
        // TODO
        event ready_event;
        players_output_events.push_back(ready_event);
    }
}

void server::worker::proceedGames() {
    // TODO Under construction
}

void server::worker::sendPlayerEvents() {
    for (auto &&outputEvent : players_output_events) {
//        outputEvent.execute();
    }
}

void server::worker::sendGamesEvents() {
    // placeholder
}


