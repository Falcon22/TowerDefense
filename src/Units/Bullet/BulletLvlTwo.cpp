#include "BulletLvlTwo.h"

BulletLvlTwo::BulletLvlTwo(const sf::Vector2f &position, float angle, Warrior &target)
        : Bullet(Type::lvlTwo, position, target, kDamage_, kVelocity_, angle) {}

