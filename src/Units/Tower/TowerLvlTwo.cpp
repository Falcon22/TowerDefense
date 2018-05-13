#include "TowerLvlTwo.h"
#include "../Bullet/BulletLvlTwo.h"

TowerLvlTwo::TowerLvlTwo(const sf::Vector2f& position, std::list<std::shared_ptr<Warrior>>& warriors,
                         std::vector<std::shared_ptr<Bullet>>& bullets)
        : Tower(Type::lvlTwo, position, kPrice_, kAttackRange_, kAttackCooldown_, warriors, bullets) {}

std::shared_ptr<Bullet> TowerLvlTwo::makeBullet() {
    double radAngle = angle_ * M_PI / 180 - M_PI / 2;
    return std::make_shared<BulletLvlTwo>(position_+ sf::Vector2f(30 * cos(radAngle), 30 * sin(radAngle)), angle_, target_);
}