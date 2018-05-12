#include "GraphicsUnitManager.h"


GraphicsUnitManager::GraphicsUnitManager(States::Context& context ,Castle& castle1, Castle& castle2)
        : gCastle1(new GraphicsCastle(context, castle1)),
          gCastle2(new GraphicsCastle(context, castle2)),
          gBullets(),
          gExplodedBullets() {}

GraphicsUnitManager::~GraphicsUnitManager() {
    delete gCastle1;
    delete gCastle2;
    for (auto gBullet: gBullets) {
        delete gBullet;
    }
    for (auto gExplbullet: gExplodedBullets) {
        delete gExplbullet;
    }
}

void GraphicsUnitManager::update(const sf::Time& dt, States::Context& context, const std::vector<Bullet*>& bullets) {
    gCastle1->update(dt, context);
    gCastle2->update(dt, context);

    if (bullets.size() > gBullets.size()) {
        auto realBulletsIterator = bullets.end();
        for (size_t i = 0; i < bullets.size() - gBullets.size(); ++i) {
            realBulletsIterator--;
            gBullets.push_back(new GraphicsBullet(*realBulletsIterator, context));
        }
    }
    for (auto gBullet = gBullets.begin(); gBullet != gBullets.end();) {
        if ((*gBullet)->isExploded() || (*gBullet)->isFinished()) {
            if ((*gBullet)->isFinished()) {
                delete *gBullet;
            } else {
                gExplodedBullets.push_back(*gBullet);
            }
            gBullet = gBullets.erase(gBullet);
        } else {
            (*gBullet)->update(dt);
            ++gBullet;
        }
    }
    for (auto gExplBullet = gExplodedBullets.begin(); gExplBullet != gExplodedBullets.end();) {
        if ((*gExplBullet)->isFinished()) {
            delete *gExplBullet;
            gExplBullet = gExplodedBullets.erase(gExplBullet);
        } else {
            (*gExplBullet)->update(dt);
            ++gExplBullet;
        }
    }
}

void GraphicsUnitManager::draw(States::Context& context) {
    for (auto gBullet: gBullets) {
        gBullet->draw(context);
    }
    gCastle1->draw(context);
    gCastle2->draw(context);
    for (auto gExplBullet: gExplodedBullets) {
        gExplBullet->draw(context);
    }
}
