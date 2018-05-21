#ifndef TOWERDEFENSE_TOWER_H
#define TOWERDEFENSE_TOWER_H

#include <vector>
#include <list>
#include <cmath>
#include "../GameUnit.h"
#include "../../GameConstants.h"

class Warrior;
class Bullet;

class Tower: public GameUnit {
public:

    void update(const sf::Time& dTime) override;
    static int upgrade(std::shared_ptr<Tower>& tower);
    float getAngle() const;
    int getPrice();

    GameConstants& gameConst = GameConstants::instance();

protected:
    Tower(Type type, const sf::Vector2f& position, int price, float attackRange, float attackCooldown,
          std::list<std::shared_ptr<Warrior>>& warriors, std::vector<std::shared_ptr<Bullet>>& bullets);


    bool inRange(const sf::Vector2f& pointPosition) const;
    float aim() const;
    void shoot(const sf::Time& dTime);
    virtual std::shared_ptr<Bullet> makeBullet() = 0;

    int price_;
    float angle_;
    float attackRange_;
    float cooldown_;
    float attackCooldown_;
    std::shared_ptr<Warrior> target_;
    std::list<std::shared_ptr<Warrior>>& warriors_;
    std::vector<std::shared_ptr<Bullet>>& bullets_;
};


#endif //TOWERDEFENSE_TOWER_H