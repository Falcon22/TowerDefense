#ifndef TOWERDEFENSE_TOWERLVLONE_H
#define TOWERDEFENSE_TOWERLVLONE_H


#include "Tower.h"
#include "../../Constants.h"
#include <list>
class TowerLvlOne: public Tower {
public:
    TowerLvlOne(const sf::Vector2f& position, std::list<Warrior*>& warriors, std::vector<Bullet*>& bullets);

    Bullet* makeBullet() override;

    static const unsigned int kPrice_ = 1000;
    constexpr static const float kAttackRange_ = 10000;
    static const int kAttackCooldown_ = 10;
};


#endif //TOWERDEFENSE_TOWERLVLONE_H