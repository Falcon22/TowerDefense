#include "WarriorLvlTwo.h"


WarriorLvlTwo::WarriorLvlTwo(const sf::Vector2f &position, const Map::LogicMap &logicMap)
        : Warrior(Type::lvlTwo, position, logicMap, kCost_, kVelocity_, kHp_) {}