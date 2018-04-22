#ifndef TOWERDEFENSE_WARRIORLVLTWO_H
#define TOWERDEFENSE_WARRIORLVLTWO_H


#include "Warrior.h"

class WarriorLvlTwo: public Warrior {
public:
    WarriorLvlTwo(const sf::Vector2f& position, const Map::LogicMap& logicMap);

    static const unsigned int kCost_ = 300;
    constexpr static const float kVelocity_ = 30;
    static const int kHp_ = 1000;

    const Type type_ = Type ::lvlTwo;
};


#endif //TOWERDEFENSE_WARRIORLVLTWO_H
