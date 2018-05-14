#include "BulletLvlTwo.h"

BulletLvlTwo::BulletLvlTwo(const sf::Vector2f &position, float angle, const std::shared_ptr<Warrior>& target)
        : Bullet(Type::lvlTwo, position, target, kDamage_, kVelocity_, angle) {}

