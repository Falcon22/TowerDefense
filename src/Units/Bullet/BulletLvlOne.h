#ifndef TOWERDEFENSE_BULLETLVLONE_H
#define TOWERDEFENSE_BULLETLVLONE_H


#include "Bullet.h"

class BulletLvlOne: public Bullet {
public:
    BulletLvlOne(const sf::Vector2f& position, float angle, const std::shared_ptr<Warrior>& target);
};


#endif //TOWERDEFENSE_BULLETLVLONE_H