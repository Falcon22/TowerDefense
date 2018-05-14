#include "BulletLvlOne.h"

BulletLvlOne::BulletLvlOne(const sf::Vector2f &position, float angle,const std::shared_ptr<Warrior>& target)
    : Bullet(Type::lvlOne, position, target, kDamage_, kVelocity_, angle) {}
