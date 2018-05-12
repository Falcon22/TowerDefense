#include "TowerLvlTwo.h"
#include "../Bullet/BulletLvlOne.h"
#include "../Bullet/BulletLvlTwo.h"

TowerLvlTwo::TowerLvlTwo(const sf::Vector2f& position, std::list<Warrior*>& warriors,
                         std::vector<Bullet*>& bullets)
        : Tower(Type::lvlTwo, position, kPrice_, kAttackRange_, kAttackCooldown_, warriors, bullets) {}

Bullet* TowerLvlTwo::makeBullet() {
    return new BulletLvlTwo(position_, angle_, *target_);
}