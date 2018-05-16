#include "GraphicsCastle.h"
#include "../../Castle/Castle.h"

GraphicsCastle::GraphicsCastle(States::Context& context, Castle& castle)
        : castle_(castle),
          gWarriors_(),
          gTower_(std::make_unique<GraphicsTower>(context)) {
    for (auto warrior: castle.getWarriors()) {
        gWarriors_.push_back(std::make_shared<GraphicsWarrior>(warrior, context));
    }
}

void GraphicsCastle::update(const sf::Time& dTime, States::Context& context) {
    size_t numRealWarriors = castle_.getWarriors().size();
    size_t numGWarriors = gWarriors_.size();

    if (numRealWarriors > numGWarriors) {
        auto realWarriorsIterator = castle_.getWarriors().end();
        for (size_t i = 0; i < numRealWarriors - numGWarriors; ++i) {
            realWarriorsIterator--;
            gWarriors_.push_back(std::make_shared<GraphicsWarrior>(*realWarriorsIterator, context));
        }
    }
    for (auto gWarrior = gWarriors_.begin(); gWarrior != gWarriors_.end();) {
        (*gWarrior)->update(dTime);
        if ((*gWarrior)->isFinished()) {
            gWarrior = gWarriors_.erase(gWarrior);
        } else {
            ++gWarrior;
        }
    }
}

void GraphicsCastle::draw(States::Context& context, int id) {
    for (const auto &gWarrior: gWarriors_) {
        gWarrior->draw(context);
    }
    for (const auto &tower: castle_.getTowers()) {
        gTower_->draw(context, tower, id);
    }
}