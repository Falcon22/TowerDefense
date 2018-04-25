#include "TowerLvlThree.h"
#include "../Bullet/BulletLvlTwo.h"


TowerLvlThree::TowerLvlThree(const sf::Vector2f& position, std::vector<Warrior*>& warriors,
                         std::vector<Bullet*>& bullets)
        : Tower(Type::lvlThree, position, kPrice_, kAttackRange_, kAttackCooldown_, warriors, bullets) {}

Bullet* TowerLvlThree::makeBullet() {
    return new BulletLvlTwo(position_, angle_, *target_, warriors_);
}
