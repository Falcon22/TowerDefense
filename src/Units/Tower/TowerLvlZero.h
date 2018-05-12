#ifndef TOWERDEFENSE_TOWERLVLZERO_H
#define TOWERDEFENSE_TOWERLVLZERO_H


#include "Tower.h"

class TowerLvlZero: public Tower {
public:
    TowerLvlZero(const sf::Vector2f& position, std::list<Warrior*>& warriors, std::vector<Bullet*>& bullets);

    void update(const sf::Time& dTime) override {};

private:
    Bullet* makeBullet() override;
};


#endif //TOWERDEFENSE_TOWERLVLZERO_H