#include "GraphicsUnitManager.h"


GraphicsUnitManager::GraphicsUnitManager(States::Context& context ,Castle& castle1, Castle& castle2)
        : gCastle1(std::make_shared<GraphicsCastle>(GraphicsCastle(context, castle1))),
          gCastle2(std::make_shared<GraphicsCastle>(GraphicsCastle(context, castle2))),
          gBullets(),
          intactBulletsCounter(0) {}

void GraphicsUnitManager::update(const sf::Time& dt, States::Context& context, const std::vector<std::shared_ptr<Bullet>>& bullets) {
    gCastle1->update(dt, context);
    gCastle2->update(dt, context);

    if (bullets.size() > intactBulletsCounter) {
        auto realBulletsIterator = bullets.end();
        for (size_t i = 0; i < bullets.size() - intactBulletsCounter; ++i) {
            realBulletsIterator--;
            gBullets.push_back(std::make_shared<GraphicsBullet>(GraphicsBullet(*realBulletsIterator, context)));
        }
        intactBulletsCounter = bullets.size();
    }

    for (auto gBullet = gBullets.begin(); gBullet != gBullets.end();) {
        if ((*gBullet)->isFinished()) {
            gBullet = gBullets.erase(gBullet);
        } else {

            if ((*gBullet)->update(dt)) {
                --intactBulletsCounter;
            }
            ++gBullet;
        }
    }
}

void GraphicsUnitManager::draw(States::Context& context) {
    gCastle1->draw(context);
    gCastle2->draw(context);
    for (const auto &gBullet: gBullets) {
        gBullet->draw(context);
    }
}