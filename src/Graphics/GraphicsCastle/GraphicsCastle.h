#ifndef TOWERDEFENSE_GRAPHICSCASTLE_H
#define TOWERDEFENSE_GRAPHICSCASTLE_H


#include <SFML/Graphics/Sprite.hpp>
#include "../../GameContext.h"
#include "../GraphicsUnit/GraphicsWarrior.h"
#include "../GraphicsUnit/GraphicsTower.h"

class Castle;

class GraphicsCastle {
public:
    GraphicsCastle(States::Context& context, Castle& castle);
    void update(const sf::Time& dTime);
    void draw();

    void addGWarrior(const Warrior* warrior);

private:
    Castle& castle_;
    States::Context& context_;
    std::list<GraphicsWarrior*> gWarriors_;
    GraphicsTower* gTower_;
};


#endif //TOWERDEFENSE_GRAPHICSCASTLE_H
