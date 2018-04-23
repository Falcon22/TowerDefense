#include "WarriorLvlOne.h"


WarriorLvlOne::WarriorLvlOne(const sf::Vector2f &position, const Map::LogicMap &logicMap)
    : Warrior(Type::lvlOne, position, logicMap, kCost_, kVelocity_, kHp_) {}
