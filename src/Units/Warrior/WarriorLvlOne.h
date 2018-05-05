#ifndef TOWERDEFENSE_WARRIORLVLONE_H
#define TOWERDEFENSE_WARRIORLVLONE_H


#include "Warrior.h"

class WarriorLvlOne: public Warrior {
public:
    WarriorLvlOne(const sf::Vector2f& position, const Map::LogicMap& logicMap);

    static const unsigned int kCost_ = 100;
    constexpr static const float kVelocity_ = 100;
    static const int kHp_ = 600;
};


#endif //TOWERDEFENSE_WARRIORLVLONE_H
