#ifndef TOWERDEFENSE_TOWERLVLTWO_H
#define TOWERDEFENSE_TOWERLVLTWO_H


#include "Tower.h"
#include "../../Constants.h"

class TowerLvlTwo: public Tower {
public:
    TowerLvlTwo(const sf::Vector2f& position, std::list<std::shared_ptr<Warrior>>& warriors, std::vector<std::shared_ptr<Bullet>>& bullets);

    std::shared_ptr<Bullet> makeBullet() override;

    static const unsigned int kPrice_ = 2000;
    constexpr static const float kAttackRange_ = 400;
    static const int kAttackCooldown_ = 1;
};



#endif //TOWERDEFENSE_TOWERLVLTWO_H