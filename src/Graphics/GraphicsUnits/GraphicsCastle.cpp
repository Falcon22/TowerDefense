#include "GraphicsCastle.h"
#include "../../Castle/Castle.h"

GraphicsCastle::GraphicsCastle(States::Context& context, Castle& castle)
        : castle_(castle),
          gWarriors_(),
          deadGWarriors_(),
          gTower_(new GraphicsTower(context)) {
    for (auto warrior: castle.getWarriors()) {
        gWarriors_.push_back(new GraphicsWarrior(warrior, context));
    }
}

void GraphicsCastle::update(const sf::Time& dTime, States::Context& context) {
    size_t numRealWarriors = castle_.getWarriors().size();
    size_t numGWarriors = gWarriors_.size();

    if (numRealWarriors > numGWarriors) {
        auto realWarriorsIterator = castle_.getWarriors().end();
        for (size_t i = 0; i < numRealWarriors - numGWarriors; ++i) {
            realWarriorsIterator--;
            gWarriors_.push_back(new GraphicsWarrior(*realWarriorsIterator, context));
        }
    }
    for (auto gWarrior = gWarriors_.begin(); gWarrior != gWarriors_.end();) {
        (*gWarrior)->update(dTime);
        if ((*gWarrior)->isFinished() || ((*gWarrior)->isDied())) {
            if ((*gWarrior)->isDied()) {
                deadGWarriors_.push_back(*gWarrior);
            } else {
                delete *gWarrior;
            }
            gWarrior = gWarriors_.erase(gWarrior);
        } else {
            ++gWarrior;
        }
    }
    for (auto deadGWarrior = deadGWarriors_.begin(); deadGWarrior != deadGWarriors_.end();) {
        (*deadGWarrior)->update(dTime);
        if ((*deadGWarrior)->isFinished()) {
            delete *deadGWarrior;
            deadGWarrior = deadGWarriors_.erase(deadGWarrior);
        } else {
            ++deadGWarrior;
        }
    }
}

void GraphicsCastle::draw(States::Context& context) {
    for (auto deadGWarrior: deadGWarriors_) {
        deadGWarrior->draw(context);
    }
    for (auto gWarrior: gWarriors_) {
        gWarrior->draw(context);
    }
    for (auto tower: castle_.getTowers()) {
        gTower_->draw(context, tower);
    }
}