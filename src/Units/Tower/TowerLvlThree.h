#ifndef TOWERDEFENSE_TOWERLVLTHREE_H
#define TOWERDEFENSE_TOWERLVLTHREE_H


#include "Tower.h"

class TowerLvlThree: public Tower {
public:
    TowerLvlThree(const sf::Vector2f& position, std::list<std::shared_ptr<Warrior>>& warriors, std::vector<std::shared_ptr<Bullet>>& bullets);

    std::shared_ptr<Bullet> makeBullet() override;

    static const unsigned int kPrice_ = 2000;
    constexpr static const float kAttackRange_ = 10000;
    static const int kAttackCooldown_ = 5;
};


#endif //TOWERDEFENSE_TOWERLVLTHREE_H