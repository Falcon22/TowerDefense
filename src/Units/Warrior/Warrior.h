#ifndef TOWERDEFENSE_WARRIOR_H
#define TOWERDEFENSE_WARRIOR_H


#include "../../Map.h"
#include "../GameUnit.h"
#include "../../GameConstants.h"

class Warrior: public GameUnit {
public:

    void update(const sf::Time& dTime) override;
    void suffer(int damage);

    float getDirection() const;
    int getHp() const;
    const unsigned int getCost() const;
    bool isAlive() const;
    bool isFinished() const;


protected:
    Warrior(Type type, const sf::Vector2f& position, const Map::LogicMap& logicMap, unsigned int cost,
            float velocity, int hp);

private:
    float direction_;
    float velocity_;
    int hp_;
    const unsigned int cost_;
    bool alive_;
    bool finished_;
    const Map::LogicMap& logicMap_;
};


#endif //TOWERDEFENSE_WARRIOR_H
