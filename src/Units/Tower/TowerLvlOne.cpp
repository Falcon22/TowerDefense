#include "TowerLvlOne.h"
#include "../Bullet/BulletLvlOne.h"

TowerLvlOne::TowerLvlOne(const sf::Vector2f& position, std::list<Warrior*>& warriors,
                         std::vector<Bullet*>& bullets)
        : Tower(Type::lvlOne, position, kPrice_, kAttackRange_, kAttackCooldown_, warriors, bullets) {}

Bullet* TowerLvlOne::makeBullet() {
    return new BulletLvlOne(position_, angle_, *target_);
}