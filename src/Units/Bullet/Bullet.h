#ifndef TOWERDEFENSE_BULLET_H
#define TOWERDEFENSE_BULLET_H


#include "../GameUnit.h"
#include "../Warrior/Warrior.h"

class Bullet: public GameUnit {
public:

    void update(const sf::Time& dTime) override;

    float getAngle() const;

    bool isExploded() const;

protected:
    Bullet(Type type, const sf::Vector2f& position, Warrior& target, int damage, float velocity, float angle);
    virtual void damage();
private:
    bool checkCollisionWithTarget();

    Warrior& target_;
    int damage_;
    float velocity_;
    float angle_;
    float duration_;
    bool exploded_;
    bool disappeared_;
};


#endif //TOWERDEFENSE_BULLET_H
