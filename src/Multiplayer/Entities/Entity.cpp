//
// Created by silvman on 16.05.18.
//

#include "Entity.h"

int mp::entity::getId() const {
    return id;
}

void mp::entity::setId(int id) {
    entity::id = id;
}

mp::entity::entity(int id): id(id) { }
