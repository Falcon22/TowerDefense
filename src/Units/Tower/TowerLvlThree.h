#ifndef TOWERDEFENSE_TOWERLVLTHREE_H
#define TOWERDEFENSE_TOWERLVLTHREE_H


#include "Tower.h"
#include "../../Constants.h"

class TowerLvlThree: public Tower {
public:
    TowerLvlThree(const sf::Vector2f& position, std::list<Warrior*>& warriors, std::vector<Bullet*>& bullets);

    Bullet* makeBullet() override;

    static const unsigned int kPrice_ = 2000;
    constexpr static const float kAttackRange_ = 10000;
    static const int kAttackCooldown_ = 10;
};


#endif //TOWERDEFENSE_TOWERLVLTHREE_H