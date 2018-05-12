#ifndef SERVER_GRAPHICSCASTLE_H
#define SERVER_GRAPHICSCASTLE_H


#include <SFML/Graphics/Sprite.hpp>
#include "../../GameContext.h"
#include "GraphicsWarrior.h"
#include "GraphicsTower.h"

class Castle;

class GraphicsCastle {
public:
    GraphicsCastle(States::Context& context, Castle& castle);
    void update(const sf::Time& dTime, States::Context& context);
    void draw(States::Context& context);

private:
    Castle& castle_;
    std::list<GraphicsWarrior*> gWarriors_;
    std::vector<GraphicsWarrior*> deadGWarriors_;
    GraphicsTower* gTower_;
};


#endif //SERVER_GRAPHICSCASTLE_H
