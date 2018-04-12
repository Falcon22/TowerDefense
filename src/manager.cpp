//
// Created by silvman on 08.04.18.
//

#include "manager.hpp"

template<typename T>
std::list<T>& server::manager<T>::getEntities() {
    return entities;
}

server::player_manager::player_manager(): manager(), next_id(1) { }

server::player &server::player_manager::get_by_id(int id) {
    for (auto &&player : entities)
        if (player.getId() == id)
            return player;

    throw std::logic_error("[player_manager::get_by_id] id not found");
}

void server::player_manager::add(server::player &&entity) {
    entity.setId(next_id);
    next_id++;

    entities.push_back(entity);
}

void server::player_manager::remove(int id) {
    for (auto it = entities.begin(); it != entities.end(); ++it)
        if (it->getId() == id)
            entities.erase(it);

    throw std::logic_error("[player_manager::remove] id not found");
}

server::player_manager::~player_manager() {
    for (auto &&item : entities) {
        // TODO нужно ли
        item.disconnect(); // устанавливает флаг отключенности
    }
}


server::game_manager::game_manager(): manager() { }

server::game &server::game_manager::get_by_id(int id) {
    for (auto &&game : entities)
        if (game.getId() == id)
            return game;

    throw std::logic_error("[game_manager::get_by_id] id not found");
}

void server::game_manager::add(server::game &&entity) {
    entities.push_back(entity);
}

void server::game_manager::remove(int id) {
    for (auto it = entities.begin(); it != entities.end(); ++it)
        if (it->getId() == id)
            entities.erase(it);

    throw std::logic_error("[game_manager::remove] id not found");
}
