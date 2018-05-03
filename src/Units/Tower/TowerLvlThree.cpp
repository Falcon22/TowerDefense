#include "TowerLvlThree.h"
#include "../Bullet/BulletLvlTwo.h"


TowerLvlThree::TowerLvlThree(const sf::Vector2f& position, std::list<Warrior*>& warriors,
<<<<<<< Updated upstream
                         std::vector<Bullet*>& bullets)
=======
                         std::list<Bullet*>& bullets)
>>>>>>> Stashed changes
        : Tower(Type::lvlThree, position, kPrice_, kAttackRange_, kAttackCooldown_, warriors, bullets) {}

Bullet* TowerLvlThree::makeBullet() {
    return new BulletLvlTwo(position_, angle_, *target_, warriors_);
}
