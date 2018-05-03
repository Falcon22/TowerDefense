#include "TowerLvlZero.h"
#include "../Bullet/BulletLvlOne.h"


TowerLvlZero::TowerLvlZero(const sf::Vector2f& position, std::list<Warrior*>& warriors,
                           std::vector<Bullet*>& bullets)
    : Tower(Type::lvlZero, position, 0, 0, 0, warriors, bullets) {}

Bullet* TowerLvlZero::makeBullet() {
    return nullptr;
}
