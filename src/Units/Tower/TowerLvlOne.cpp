#include "TowerLvlOne.h"
#include "../Bullet/BulletLvlOne.h"

TowerLvlOne::TowerLvlOne(const sf::Vector2f& position, std::vector<Warrior*>& warriors,
                         std::vector<Bullet*>& bullets)
    : Tower(type_, position, kPrice_, kAttackRange_, kAttackCooldown_, warriors, bullets) {}

Bullet* TowerLvlOne::makeBullet() {
    return new BulletLvlOne(position_, angle_, *target_);
}
