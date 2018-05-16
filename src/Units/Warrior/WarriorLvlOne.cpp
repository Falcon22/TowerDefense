#include "WarriorLvlOne.h"


WarriorLvlOne::WarriorLvlOne(const sf::Vector2f &position, const Map::LogicMap &logicMap)
    : Warrior(Type::lvlOne, position, logicMap, GameConstants::instance().cWARRIOR_1_COST(),
              GameConstants::instance().cWARRIOR_1_VELOCITY(), GameConstants::instance().cWARRIOR_1_HP()) {}
