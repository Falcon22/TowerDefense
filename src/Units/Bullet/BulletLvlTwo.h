#ifndef TOWERDEFENSE_BULLETLVLTWO_H
#define TOWERDEFENSE_BULLETLVLTWO_H


#include "Bullet.h"

class BulletLvlTwo: public Bullet {
public:
    BulletLvlTwo(const sf::Vector2f& position, float angle, const std::shared_ptr<Warrior>& target);
};


#endif //TOWERDEFENSE_BULLETLVLTWO_H