#ifndef TOWERDEFENSE_WARRIORLVLONE_H
#define TOWERDEFENSE_WARRIORLVLONE_H


#include "Warrior.h"

class WarriorLvlOne: public Warrior {
public:
    WarriorLvlOne(const sf::Vector2f& position, const Map::LogicMap& logicMap);
};


#endif //TOWERDEFENSE_WARRIORLVLONE_H
