#ifndef TOWERDEFENSE_TOWERLVLTWO_H
#define TOWERDEFENSE_TOWERLVLTWO_H


#include "Tower.h"
#include "../../Constants.h"

class TowerLvlTwo: public Tower {
public:
    TowerLvlTwo(const sf::Vector2f& position, std::list<Warrior*>& warriors, std::vector<Bullet*>& bullets);

    Bullet* makeBullet() override;

    static const unsigned int kPrice_ = 2000;
    constexpr static const float kAttackRange_ = 10000 * TILE_SIZE;
    static const int kAttackCooldown_ = 5;
};



#endif //TOWERDEFENSE_TOWERLVLTWO_H
