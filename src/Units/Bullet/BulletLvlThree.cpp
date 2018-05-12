#include "BulletLvlThree.h"

BulletLvlThree::BulletLvlThree(const sf::Vector2f &position, float angle, Warrior &target,
                           std::list<Warrior *> &warriors)
        : Bullet(Type::lvlThree, position, target, kDamage_, kVelocity_, angle),
          warriors_(warriors){}

void BulletLvlThree::damage() {
    for (auto warrior: warriors_) {
        if (inRange(warrior->getPosition()) && warrior->isAlive()) {
            warrior->suffer(damage_);
        }
    }
}

bool BulletLvlThree::inRange(const sf::Vector2f& pointPosition) {
    return (pointPosition.x - position_.x) * (pointPosition.x - position_.x)
           + (pointPosition.y - position_.y) * (pointPosition.y - position_.y) <= rangeAOE_ * rangeAOE_;
}