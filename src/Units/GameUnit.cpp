#include "GameUnit.h"

GameUnit::GameUnit(Type type, const sf::Vector2f &position)
        : type_(type),
          position_(position) {}

Type GameUnit::getType() const {
    return type_;
}

const sf::Vector2f &GameUnit::getPosition() const {
    return position_;
}
