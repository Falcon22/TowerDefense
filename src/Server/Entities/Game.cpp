//
// Created by silvman on 16.05.18.
//

#include "Game.h"

bool mp::game::isReady() const {
    return (first_connected_ && second_connected_);
}

void mp::game::join(int player_id) {
    if (is_started_)
        throw std::logic_error(msg::game_running);

    if (!first_connected_) {
        player_id_first_ = player_id;
        first_connected_ = true;
    } else if (!second_connected_) {
        player_id_second_ = player_id;
        second_connected_ = true;
    }
}

const std::string &mp::game::getName() const {
    return name_;
}

mp::game::game(const std::string &name) :
        name_(name),
        is_started_(false),
        first_connected_(false),
        second_connected_(false),
        player_id_second_(0),
        player_id_first_(0)
{ }

bool mp::game::isStarted() const {
    return is_started_;
}

void mp::game::start() {
    is_started_ = true;
}

int mp::game::getFirstId() const {
    return player_id_first_;
}

int mp::game::getSecondId() const {
    return player_id_second_;
}