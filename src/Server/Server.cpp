//
// Created by silvman on 08.04.18.
//

#include <iostream>
#include <unistd.h>
#include "Server.h"

mp::master::master(unsigned short port): running_(true) {
    if (listener_.listen(port) != sf::Socket::Status::Done) {
        running_ = false;
    };
    selector_.add(listener_);
}

mp::master::~master() {
    listener_.close(); // TODO Нужно?
}

void mp::master::work() {
    std::cout << msg::run << std::endl;
    while (running_) try {
        if (selector_.wait(constants::waitTime())) {
            if (selector_.isReady(listener_)) { // подключение нового игрока
                player& new_player = pool_players_.create(); // добавление игрока в список

                try {
                    new_player.connect(listener_, selector_);
                } catch (const std::exception& e) {
                    // если ошибка при подключении
                    std::cout << e.what();
                    pool_players_.remove(new_player.getId());
                }

            } else {
                for (auto &&player : pool_players_.getEntities()) {
                    if (!player.isInGame() && selector_.isReady(player.getSocket())) {
                        try {
                            player.getEvents();
                        } catch (const std::exception& e) {
                            // сюда попадаем при проблемах с подключением игрока. Пока что просто удаляем его, в дальнейшем можно было бы обработать
                            std::cout << e.what() << std::endl;
                            selector_.remove(player.getSocket());
                        }

                        // обрабатываем создание новых игр и подключение к ним
                        proceedEvents(player);
                        player.from_client.clear();
                    }
                }
            }
        } else {
            for (auto &&game : pool_games_) {
                if (game.isReady() && !game.isStarted()) {
                    startWorker(game);
                }
            }
        }
    } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
    }

//    wait();
}

void mp::master::proceedEvents(player &player) {
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
            std::cout << msg::join << player.getId() << " " << pending_game_id << std::endl;

            // TODO подключение по именам
        } else if (event.type == 'n') {
            pool_games_.emplace_back(event.value); // name - имя игры

            player.to_send.emplace_back(0, 'n', std::to_string(pool_games_.size() - 1),
                                        sf::microseconds(0));

            std::cout << msg::add_game << event.value << std::endl;

            player.sendEvents();
        }
    }

}

void mp::master::startWorker(mp::game &game) {
    pid_t pid = fork();

    switch (pid) {
        case 0: {
            game.start();
            selector_.remove(pool_players_.get_by_id(game.getFirstId()).getSocket());
            selector_.remove(pool_players_.get_by_id(game.getSecondId()).getSocket());
            std::cout << msg::success << pid << std::endl;
            break;
        } // возможно, действия, связанные с обеспечением безопасности игры

        case -1: {
            std::cout << msg::error << std::endl;
            break;
        }

        default: {
            running_ = false; // worker не должен продолжать цикл master

            worker worker(pool_players_.get_by_id(game.getFirstId()), pool_players_.get_by_id(game.getSecondId()), pid);
            worker.work();

            return;
        }

    }
}


mp::worker::worker(player &first, player &second, pid_t pid)
        : first_(first), second_(second), pid_(pid), game_(first, second) {
    std::cout << msg::success << pid << std::endl;

    first_.setId(1);
    second_.setId(2);
}

void mp::worker::work() {
    std::cout << msg::run << pid_ << std::endl;

    // Отсылаем сообщения о начале игры (включает в себя айдишники)
    try {
        first_.startGame();
        second_.startGame();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return;
    }

    game_.server_run(false);

    std::cout << msg::end << pid_ << std::endl;
}