#include "BulletLvlOne.h"

BulletLvlOne::BulletLvlOne(const sf::Vector2f &position, float angle, Warrior &target)
    : Bullet(type_, position, target, kDamage_, kVelocity_, angle) {}
