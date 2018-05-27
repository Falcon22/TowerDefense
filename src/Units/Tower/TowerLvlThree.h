#ifndef TOWERDEFENSE_TOWERLVLTHREE_H
#define TOWERDEFENSE_TOWERLVLTHREE_H


#include "Tower.h"

class TowerLvlThree: public Tower {
public:
    TowerLvlThree(const sf::Vector2f& position, std::list<std::shared_ptr<Warrior>>& warriors, std::vector<std::shared_ptr<Bullet>>& bullets);

    std::shared_ptr<Bullet> makeBullet() override;
};


#endif //TOWERDEFENSE_TOWERLVLTHREE_H