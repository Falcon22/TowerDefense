#ifndef TOWERDEFENSE_GAMEUNIT_H
#define TOWERDEFENSE_GAMEUNIT_H


#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include "../GameContext.h"

class GameUnit {
public:
    virtual void update(const sf::Time& dTime) = 0;

    Type getType() const;
    const sf::Vector2f& getPosition() const;

protected:
    GameUnit(Type type, const sf::Vector2f& position);

    Type type_;
    sf::Vector2f position_;
};


#endif //TOWERDEFENSE_GAMEUNIT_H
