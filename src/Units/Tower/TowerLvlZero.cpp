#include "TowerLvlZero.h"
#include "../Bullet/BulletLvlOne.h"


TowerLvlZero::TowerLvlZero(const sf::Vector2f& position, std::vector<Warrior*>& warriors,
                           std::vector<Bullet*>& bullets)
    : Tower(type_, position, 0, 0, 0, warriors, bullets) {}

Bullet* TowerLvlZero::makeBullet() {
    return nullptr;
}
