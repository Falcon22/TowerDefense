#include "WarriorLvlTwo.h"


WarriorLvlTwo::WarriorLvlTwo(const sf::Vector2f &position, const Map::LogicMap &logicMap)
        : Warrior(Type::lvlTwo, position, logicMap, GameConstants::instance().cWARRIOR_2_COST(),
                  GameConstants::instance().cWARRIOR_2_VELOCITY(), GameConstants::instance().cWARRIOR_2_HP()) {}