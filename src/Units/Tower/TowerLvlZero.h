#ifndef TOWERDEFENSE_TOWERLVLZERO_H
#define TOWERDEFENSE_TOWERLVLZERO_H


#include "Tower.h"

class TowerLvlZero: public Tower {
public:
    TowerLvlZero(const sf::Vector2f& position, std::list<std::shared_ptr<Warrior>>& warriors, std::vector<std::shared_ptr<Bullet>>& bullets);

    void update(const sf::Time& dTime) override {};

private:
    std::shared_ptr<Bullet> makeBullet() override;
};


#endif //TOWERDEFENSE_TOWERLVLZERO_H