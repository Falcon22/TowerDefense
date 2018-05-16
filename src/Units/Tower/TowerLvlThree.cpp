
#include "TowerLvlThree.h"
#include "../Bullet/BulletLvlThree.h"


TowerLvlThree::TowerLvlThree(const sf::Vector2f& position, std::list<std::shared_ptr<Warrior>>& warriors,
                             std::vector<std::shared_ptr<Bullet>>& bullets)
        : Tower(Type::lvlThree, position, -1, GameConstants::instance().cTOWER_3_RANGE(),
                GameConstants::instance().cTOWER_3_COOLDOWN(), warriors, bullets) {}

std::shared_ptr<Bullet> TowerLvlThree::makeBullet() {
    double radAngle = angle_ * M_PI / 180 - M_PI / 2;
    return std::make_shared<BulletLvlThree>(position_ + sf::Vector2f(35 * cos(radAngle), 35 * sin(radAngle)), angle_, target_, warriors_);
}