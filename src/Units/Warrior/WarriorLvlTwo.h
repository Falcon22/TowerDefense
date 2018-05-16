#ifndef TOWERDEFENSE_WARRIORLVLTWO_H
#define TOWERDEFENSE_WARRIORLVLTWO_H


#include "Warrior.h"

class WarriorLvlTwo: public Warrior {
public:
    WarriorLvlTwo(const sf::Vector2f& position, const Map::LogicMap& logicMap);

    static const unsigned int kCost_ = 300;
    constexpr static const float kVelocity_ = 200;
    static const int kHp_ = 2000;
};


#endif //TOWERDEFENSE_WARRIORLVLTWO_H

