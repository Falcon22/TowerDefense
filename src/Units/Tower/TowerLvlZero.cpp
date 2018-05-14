#include "TowerLvlZero.h"
#include "../Bullet/BulletLvlOne.h"


TowerLvlZero::TowerLvlZero(const sf::Vector2f& position, std::list<std::shared_ptr<Warrior>>& warriors,
                           std::vector<std::shared_ptr<Bullet>>& bullets)
        : Tower(Type::lvlZero, position, 0, 0, 0, warriors, bullets) {}

std::shared_ptr<Bullet> TowerLvlZero::makeBullet() {
    return nullptr;
}