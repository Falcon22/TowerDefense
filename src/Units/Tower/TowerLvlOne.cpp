#include "TowerLvlOne.h"
#include "../Bullet/BulletLvlOne.h"

TowerLvlOne::TowerLvlOne(const sf::Vector2f& position, std::list<std::shared_ptr<Warrior>>& warriors,
                         std::vector<std::shared_ptr<Bullet>>& bullets)
        : Tower(Type::lvlOne, position, GameConstants::instance().cTOWER_1_UP_COST(),
                GameConstants::instance().cTOWER_1_RANGE(), GameConstants::instance().cTOWER_1_COOLDOWN(),
                warriors, bullets) {}

std::shared_ptr<Bullet> TowerLvlOne::makeBullet() {
    double radAngle = angle_ * M_PI / 180 - M_PI / 2;
    return std::make_shared<BulletLvlOne>(position_ + sf::Vector2f(20 * cos(radAngle), 20 * sin(radAngle)), angle_, target_);
}