//
// Created by silvman on 08.04.18.
//

#include <iostream>
#include <unistd.h>
#include "Server.h"

mp::master::master(unsigned short port): running_(true) {
    listener_.listen(port);
    selector_.add(listener_);
}

mp::master::~master() {
    listener_.close(); // TODO Нужно?
}

void mp::master::work() {
    std::cout << "[run]" << '\n';
    while (running_) {
        if (selector_.wait(constants::waitTime())) {
            if (selector_.isReady(listener_)) {
                // добавление игрока в список
                player& new_player = pool_players_.create();
                try {
                    new_player.connect(listener_, selector_);
                } catch (const std::exception& e) {
                    pool_players_.remove(new_player.getId()); // TODO перенести в реализацию метода
                }

            } else {
                for (auto &&player : pool_players_.getEntities()) {
                    if (!player.isInGame() && selector_.isReady(player.getSocket())) {
                        try {
                            player.getEvents();
                        } catch (const std::exception& e) {
                            selector_.remove(player.getSocket());
                        }

                        // TODO вынести в отдельный метод
                        for (auto &&event : player.from_client) {
                            if (event.type == 'j') {
                                int pending_game_id = atoi(event.value.c_str());

                                try {
                                    pool_games_.at(pending_game_id).join(player.getId());
                                } catch (const std::exception& e) {
                                    std::cout << e.what() << std::endl;
                                    break;
                                }

                                player.setInGame();

                                std::cout << player.getId() << " join'd game " << pending_game_id << std::endl;

                                // TODO подключение по именам
//                                    for (auto &&game : pool_games_) {
//                                        if (game.getName() == pending_game_name) { // ID - индекс в
//                                            game.join(player);
//                                            break;
//                                        }
//                                    }
                            } else if (event.type == 'n') {
                                pool_games_.emplace_back(event.value); // name - имя игры

                                player.to_send.emplace_back(0, 's', std::to_string(pool_games_.size() - 1),
                                                                     sf::microseconds(0));

                                std::cout << "add game " + event.value << std::endl;

                                player.sendEvents();
                            }
                        }

                        player.from_client.clear();
                    }
                }
            }
        } else {
            for (auto &&game : pool_games_) {

                if (game.isReady() && !game.isStarted()) {
                    pid_t pid = fork();

                    switch (pid) {
                        case 0: {
                            game.start();
                            selector_.remove(pool_players_.get_by_id(game.getFirstId()).getSocket());
                            selector_.remove(pool_players_.get_by_id(game.getSecondId()).getSocket());
                            std::cout << "master: success " << pid << std::endl;
                            break;
                        } // возможно, действия, связанные с обеспечением безопасности игры

                        case -1: {
                            std::cout << "error!" << std::endl;
                            break;
                        }

                        default: {
                            running_ = false;

                            std::cout << "child: success " << pid << std::endl;
                            worker worker(pool_players_.get_by_id(game.getFirstId()), pool_players_.get_by_id(game.getSecondId()));
                            worker.work();

                            return;
                        }

                    }
                }

            }
        }
    }

    std::cout << "end" << std::endl;
}


mp::worker::worker(player &first, player &second) : first_(first), second_(second), running_(false) {
    selector_.add(first.getSocket());
    selector_.add(second.getSocket());


    first_.setId(1);
    second_.setId(2);
}

void mp::worker::work() {
    std::cout << "[run] simple server" << '\n';

    // TODO отослать сообщения о начале игры
    try {
        first_.startGame();
        second_.startGame();
        running_ = true;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    while (running_) {
        if (!first_.isAvailable() && !second_.isAvailable())
            return;
        
        if (selector_.wait(constants::waitTime())) {
            if (first_.hasNewData(selector_)) {
                try {
                    first_.getEvents();
                } catch (const std::exception &e) {
                    selector_.remove(first_.getSocket());
                }
            }

            if (second_.hasNewData(selector_)) {
                try {
                    second_.getEvents();
                } catch (const std::exception &e) {
                    selector_.remove(second_.getSocket());
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