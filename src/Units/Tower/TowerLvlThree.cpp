#include "TowerLvlThree.h"
#include "../Bullet/BulletLvlThree.h"


TowerLvlThree::TowerLvlThree(const sf::Vector2f& position, std::list<Warrior*>& warriors,
                             std::vector<Bullet*>& bullets)
        : Tower(Type::lvlThree, position, kPrice_, kAttackRange_, kAttackCooldown_, warriors, bullets) {}

Bullet* TowerLvlThree::makeBullet() {
    return new BulletLvlThree(position_, angle_, *target_, warriors_);
}