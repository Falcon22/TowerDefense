#ifndef SERVER_GRAPHICSUNITMANAGER_H
#define SERVER_GRAPHICSUNITMANAGER_H


#include "../../Castle/Castle.h"
#include "GraphicsCastle.h"
#include "GraphicsBullet.h"

class GraphicsUnitManager {
public:
    GraphicsUnitManager(States::Context& context, Castle& castle1, Castle& castle2);

    void update(const sf::Time &dt, States::Context& context, const std::vector<std::shared_ptr<Bullet>>& bullets);
    void draw(States::Context& context);

private:
    std::shared_ptr<GraphicsCastle> gCastle1;
    std::shared_ptr<GraphicsCastle> gCastle2;

    std::vector<std::shared_ptr<GraphicsBullet>> gBullets;
    size_t intactBulletsCounter;
};


#endif //SERVER_GRAPHICSUNITMANAGER_H
