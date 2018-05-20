#include "GraphicsCastle.h"
#include "../../Castle/Castle.h"

GraphicsCastle::GraphicsCastle(States::Context& context, Castle& castle)
        : castle_(castle),
          gWarriors_(),
          gTower_(std::make_unique<GraphicsTower>(context)) {
    for (auto warrior: castle.getWarriors()) {
        gWarriors_.push_back(std::make_shared<GraphicsWarrior>(warrior, context));
    }
    numAliveWarriors_ = gWarriors_.size();
}

void GraphicsCastle::update(const sf::Time& dTime, States::Context& context) {
    size_t numRealWarriors = castle_.getWarriors().size();
    if (numRealWarriors != 0 || numAliveWarriors_ != 0) {
        std::cout << "real: " << numRealWarriors << " | alive: " << numAliveWarriors_ << std::endl;
    }
    if (numRealWarriors > numAliveWarriors_) {
        auto realWarriorsIterator = castle_.getWarriors().end();
        size_t i = 0;
        for (; i < numRealWarriors - numAliveWarriors_; ++i) {
            realWarriorsIterator--;
            gWarriors_.push_back(std::make_shared<GraphicsWarrior>(*realWarriorsIterator, context));
        }
        numAliveWarriors_ += i;
    }
    for (auto gWarrior = gWarriors_.begin(); gWarrior != gWarriors_.end();) {
        if ((*gWarrior)->update(dTime)) {
            --numAliveWarriors_;
        }

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

void GraphicsCastle::decreaseAliveWarriors() {
    --numAliveWarriors_;
}
