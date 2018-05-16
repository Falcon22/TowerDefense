#include "BulletLvlThree.h"

BulletLvlThree::BulletLvlThree(const sf::Vector2f &position, float angle, const std::shared_ptr<Warrior>& target,
                           std::list<std::shared_ptr<Warrior>> &warriors)
        : Bullet(Type::lvlThree, position, target, GameConstants::instance().cBULLET_3_DAMAGE(),
                 GameConstants::instance().cBULLET_3_VELOCITY(), angle),
          warriors_(warriors),
          rangeAOE_(GameConstants::instance().cBULLET_3_AOE()) {}

void BulletLvlThree::damage() {
    for (const auto& warrior: warriors_) {
        if (warrior != nullptr && inRange(warrior->getPosition()) && warrior->isAlive()) {
            warrior->suffer(damage_);
        }
    }
}

bool BulletLvlThree::inRange(const sf::Vector2f& pointPosition) {
    return (pointPosition.x - position_.x) * (pointPosition.x - position_.x)
           + (pointPosition.y - position_.y) * (pointPosition.y - position_.y) <= rangeAOE_ * rangeAOE_;
}