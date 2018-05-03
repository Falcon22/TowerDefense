#include "GraphicsCastle.h"
#include "../../Castle/Castle.h"

GraphicsCastle::GraphicsCastle(States::Context& context, Castle& castle)
    : context_(context),
      castle_(castle),
      gWarriors_(),
      gTower_(new GraphicsTower(context)) {
    for (auto warrior: castle.getWarriors()) {
        gWarriors_.push_back(new GraphicsWarrior(warrior, context));
    }
}

void GraphicsCastle::update(const sf::Time& dTime) {
    for (auto gWarrior = gWarriors_.begin(); gWarrior != gWarriors_.end();) {
        (*gWarrior)->update(dTime);
        if ((*gWarrior)->isFinished()) {
            delete *gWarrior;
            gWarrior = gWarriors_.erase(gWarrior);
        }
        else {
            ++gWarrior;
        }
    }
}

void GraphicsCastle::draw() {
    for (auto gWarrior: gWarriors_) {
        gWarrior->draw(context_);
    }
    for (auto tower: castle_.getTowers()) {
        gTower_->draw(context_, tower);
    }
}

void GraphicsCastle::addGWarrior(const Warrior *warrior) {
    gWarriors_.push_back(new GraphicsWarrior(warrior, context_));
}
