#ifndef SERVER_GRAPHICSUNITMANAGER_H
#define SERVER_GRAPHICSUNITMANAGER_H


#include "../../Castle/Castle.h"
#include "GraphicsCastle.h"
#include "GraphicsBullet.h"

class GraphicsUnitManager {
public:
    GraphicsUnitManager(States::Context& context, Castle& castle1, Castle& castle2);
    ~GraphicsUnitManager();

    void update(const sf::Time &dt, States::Context& context, const std::vector<Bullet*>& bullets);
    void draw(States::Context& context);

private:
    GraphicsCastle *gCastle1;
    GraphicsCastle *gCastle2;
    std::vector<GraphicsBullet *> gBullets;
    std::vector<GraphicsBullet *> gExplodedBullets;
};


#endif //SERVER_GRAPHICSUNITMANAGER_H
