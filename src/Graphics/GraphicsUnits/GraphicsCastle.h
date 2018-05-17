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
    void draw(States::Context& context, int id);

private:
    Castle& castle_;
    std::list<std::shared_ptr<GraphicsWarrior>> gWarriors_;
    std::unique_ptr<GraphicsTower> gTower_;
};


#endif //SERVER_GRAPHICSCASTLE_H
