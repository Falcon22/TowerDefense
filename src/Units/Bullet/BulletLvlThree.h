#ifndef SERVER_BULLETLVLTHREE_H
#define SERVER_BULLETLVLTHREE_H


#include "Bullet.h"
#include <list>

class BulletLvlThree: public Bullet {
public:
    BulletLvlThree(const sf::Vector2f& position, float angle, Warrior& target, std::list<Warrior*>& warriors);

    void damage() override;

    static const int kDamage_ = 200;
    constexpr static const float kVelocity_ = 200;

private:
    bool inRange(const sf::Vector2f& pointPosition);

    std::list<Warrior*>& warriors_;
    const float rangeAOE_ = 300;
};



#endif //SERVER_BULLETLVLTHREE_H
