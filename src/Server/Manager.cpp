//
// Created by silvman on 08.04.18.
//

#include "Manager.h"

template<typename T>
std::list<T>& mp::manager<T>::getEntities() {
    return entities;
}

mp::player_manager::player_manager(): manager(), next_id(1) { }

mp::player &mp::player_manager::get_by_id(int id) {
    for (auto &&player : entities)
        if (player.getId() == id)
            return player;

    throw std::logic_error("[player_manager::get_by_id] id not found");
}

void mp::player_manager::remove(int id) {
    for (auto it = entities.begin(); it != entities.end(); ++it)
        if (it->getId() == id) {
            entities.erase(it);
            return;;
        }

    throw std::logic_error("[player_manager::remove] id not found");
}

mp::player_manager::~player_manager() {
    for (auto &&item : entities) {
        // TODO нужно ли
        item.disconnect(); // устанавливает флаг отключенности
    }
}

mp::player &mp::player_manager::create() {
    entities.emplace_back(next_id);
    next_id++;

    return entities.back();
}


//mp::game_manager::game_manager(): manager(), next_id(1) { }
//
//mp::game &mp::game_manager::get_by_id(int id) {
//    for (auto &&game : entities)
//        if (game.getId() == id)
//            return game;
//
//    throw std::logic_error("[game_manager::get_by_id] id not found");
//}
//
//void mp::game_manager::remove(int id) {
//    for (auto it = entities.begin(); it != entities.end(); ++it)
//        if (it->getId() == id)
//            entities.erase(it);
//
//    throw std::logic_error("[game_manager::remove] id not found");
//}