#ifndef TOWERDEFENSE_TOWER_H
#define TOWERDEFENSE_TOWER_H

#include <vector>
#include <list>
#include <cmath>
#include "../GameUnit.h"


class Warrior;
class Bullet;

class Tower: public GameUnit {
public:

    void update(const sf::Time& dTime) override;
    static void upgrade(std::shared_ptr<Tower>& tower);
    float getAngle() const;
    unsigned int getPrice();

protected:
    Tower(Type type, const sf::Vector2f& position, unsigned int price, float attackRange, float attackCooldown,
          std::list<std::shared_ptr<Warrior>>& warriors, std::vector<std::shared_ptr<Bullet>>& bullets);

    bool inRange(const sf::Vector2f& pointPosition) const;
    float aim() const;
    void shoot(const sf::Time& dTime);
    virtual std::shared_ptr<Bullet> makeBullet() = 0;

    unsigned int price_;
    float angle_;
    float attackRange_;
    float cooldown_;
    float attackCooldown_;
    std::shared_ptr<Warrior> target_;
    std::list<std::shared_ptr<Warrior>>& warriors_;
    std::vector<std::shared_ptr<Bullet>>& bullets_;
};


#endif //TOWERDEFENSE_TOWER_H