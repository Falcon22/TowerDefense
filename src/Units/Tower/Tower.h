#ifndef TOWERDEFENSE_TOWER_H
#define TOWERDEFENSE_TOWER_H


#include <vector>
#include "../GameUnit.h"


class Warrior;
class Bullet;

class Tower: public GameUnit {
public:

    void update(const sf::Time& dTime) override;

    float getAngle() const;

protected:
    Tower(Type type, const sf::Vector2f& position, unsigned int price, float attackRange, float attackCooldown,
            std::vector<Warrior*>& warriors, std::vector<Bullet*>& bullets);

    bool inRange(const sf::Vector2f& pointPosition) const;
    float aim() const;
    void shoot(const sf::Time& dTime);
    virtual Bullet* makeBullet() = 0;

    unsigned int price_;
    float angle_;
    float attackRange_;
    float cooldown_;
    float attackCooldown_;
    Warrior* target_;
    std::vector<Warrior*>& warriors_;
    std::vector<Bullet*>& bullets_;
};


#endif //TOWERDEFENSE_TOWER_H
