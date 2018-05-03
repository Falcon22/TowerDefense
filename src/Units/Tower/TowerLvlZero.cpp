#include "TowerLvlZero.h"
#include "../Bullet/BulletLvlOne.h"


TowerLvlZero::TowerLvlZero(const sf::Vector2f& position, std::list<Warrior*>& warriors,
<<<<<<< Updated upstream
                           std::vector<Bullet*>& bullets)
    : Tower(Type::lvlZero, position, 0, 0, 0, warriors, bullets) {}
=======
                           std::list<Bullet*>& bullets)
    : Tower(type_, position, 0, 0, 0, warriors, bullets) {}
>>>>>>> Stashed changes

Bullet* TowerLvlZero::makeBullet() {
    return nullptr;
}
