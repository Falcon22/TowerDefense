#include "TowerLvlTwo.h"
#include "../Bullet/BulletLvlOne.h"

TowerLvlTwo::TowerLvlTwo(const sf::Vector2f& position, std::list<Warrior*>& warriors,
<<<<<<< Updated upstream
                         std::vector<Bullet*>& bullets)
=======
                         std::list<Bullet*>& bullets)
>>>>>>> Stashed changes
        : Tower(Type::lvlTwo, position, kPrice_, kAttackRange_, kAttackCooldown_, warriors, bullets) {}

Bullet* TowerLvlTwo::makeBullet() {
    return new BulletLvlOne(position_, angle_, *target_);
}
