#include "BulletLvlTwo.h"

BulletLvlTwo::BulletLvlTwo(const sf::Vector2f &position, float angle, const std::shared_ptr<Warrior>& target)
        : Bullet(Type::lvlTwo, position, target, GameConstants::instance().cBULLET_2_DAMAGE(),
                 GameConstants::instance().cBULLET_2_VELOCITY(), angle) {}

