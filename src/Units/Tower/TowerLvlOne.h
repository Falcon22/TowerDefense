#ifndef TOWERDEFENSE_TOWERLVLONE_H
#define TOWERDEFENSE_TOWERLVLONE_H


#include "Tower.h"
#include "../../Constants.h"

class TowerLvlOne: public Tower {
public:
    TowerLvlOne(const sf::Vector2f& position, std::list<Warrior*>& warriors, std::vector<Bullet*>& bullets);

    Bullet* makeBullet() override;

    static const unsigned int kPrice_ = 1000;
    constexpr static const float kAttackRange_ = 300;
    static const int kAttackCooldown_ = 4;
};


#endif //TOWERDEFENSE_TOWERLVLONE_H