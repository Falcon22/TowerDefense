#ifndef TOWERDEFENSE_BULLETLVLTWO_H
#define TOWERDEFENSE_BULLETLVLTWO_H


#include "Bullet.h"

class BulletLvlTwo: public Bullet {
public:
    BulletLvlTwo(const sf::Vector2f& position, float angle, Warrior& target, std::vector<Warrior*>& warriors);

    void damage() override;

    static const int kDamage_ = 100;
    constexpr static const float kVelocity_ = 100;

private:
    bool inRange(const sf::Vector2f& pointPosition);

    std::vector<Warrior*>& warriors_;
    const float rangeAOE_ = 250;
};


#endif //TOWERDEFENSE_BULLETLVLTWO_H
