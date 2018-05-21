#ifndef SERVER_BULLETLVLTHREE_H
#define SERVER_BULLETLVLTHREE_H


#include "Bullet.h"
#include <list>

class BulletLvlThree: public Bullet {
public:
    BulletLvlThree(const sf::Vector2f& position, float angle, const std::shared_ptr<Warrior>& target, std::list<std::shared_ptr<Warrior>>& warriors);

    void damage() override;

private:
    bool inRange(const sf::Vector2f& pointPosition);

    std::list<std::shared_ptr<Warrior>>& warriors_;
    float rangeAOE_;
};



#endif //SERVER_BULLETLVLTHREE_H