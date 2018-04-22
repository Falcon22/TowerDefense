#include "WarriorLvlTwo.h"


WarriorLvlTwo::WarriorLvlTwo(const sf::Vector2f &position, const Map::LogicMap &logicMap)
        : Warrior(type_, position, logicMap, kCost_, kVelocity_, kHp_) {}