#ifndef TOWERDEFENSE_BULLET_H
#define TOWERDEFENSE_BULLET_H


#include "../GameUnit.h"
#include "../Warrior/Warrior.h"
#include "../../GameConstants.h"

class Bullet: public GameUnit {
public:

    void update(const sf::Time& dTime) override;

    float getAngle() const;

    bool isExploded() const;
    bool isDisappeared() const;

protected:
    Bullet(Type type, const sf::Vector2f& position, const std::shared_ptr<Warrior>& target, int damage, float velocity, float angle);
    virtual void damage();

    bool checkCollisionWithTarget();

    std::shared_ptr<Warrior> target_;
    int damage_;
    float velocity_;
    float angle_;
    bool exploded_;
    bool disappeared_;
};


#endif //TOWERDEFENSE_BULLET_H
