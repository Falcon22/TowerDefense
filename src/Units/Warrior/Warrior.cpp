#include "Warrior.h"


Warrior::Warrior(Type type, const sf::Vector2f& position, const Map::LogicMap& logicMap, unsigned int cost,
                 float velocity, int hp)
    : GameUnit(type, position),
      logicMap_(logicMap),
      direction_(0),
      alive_(true),
      finished_(false),
      cost_(cost),
      velocity_(velocity),
      hp_(hp){
}

void Warrior::update(const sf::Time &dTime) {
    if (logicMap_.finish.contains(position_)) {
        finished_ = true;
        return;
    }
    if (hp_ <= 0) {
        alive_ = false;
        return;
    }

    Map::Direction direction = Map::UP;

    for (auto part : logicMap_.road) {
        if (part.first.contains(position_)) {
            direction = part.second;
            break;
        }
    }

    switch (direction) {
        case Map::UP:
            position_.y -= velocity_ * dTime.asSeconds();
            direction_ = 270;
            break;
        case Map::DOWN:
            position_.y += velocity_ * dTime.asSeconds();
            direction_ = 90;
            break;
        case Map::LEFT:
            position_.x -= velocity_ * dTime.asSeconds();
            direction_ = 180;
            break;
        case Map::RIGHT:
            position_.x += velocity_ * dTime.asSeconds();
            direction_ = 0;
            break;
    }
}

float Warrior::getDirection() const {
    return direction_;
}

int Warrior::getHp() const {
    return hp_;
}

const unsigned int Warrior::getCost() const {
    return cost_;
}

bool Warrior::isAlive() const {
    return alive_;
}

bool Warrior::isFinished() const {
    return finished_;
}

void Warrior::suffer(int damage) {
    std::cout << "aaaa" << std::endl;
    hp_ -= damage;
}
