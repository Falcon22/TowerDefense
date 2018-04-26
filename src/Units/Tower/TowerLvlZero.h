#ifndef TOWERDEFENSE_TOWERLVLZERO_H
#define TOWERDEFENSE_TOWERLVLZERO_H


#include "Tower.h"

class TowerLvlZero: public Tower {
public:
    TowerLvlZero(const sf::Vector2f& position, std::vector<Warrior*>& warriors, std::vector<Bullet*>& bullets);

    void update(const sf::Time& dTime) override {};

    const Type type_ = Type ::lvlZero;

private:
    Bullet* makeBullet() override;
};


#endif //TOWERDEFENSE_TOWERLVLZERO_H
