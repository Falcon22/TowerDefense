#include <cmath>
#include "Farm.h"
#include "../../GameConstants.h"

Farm::Farm()
    : Building(GameConstants::instance().cFARM_COST()),
      working(GameConstants::instance().cFARM_TIME_CYCLE()) {
}

int Farm::getBenefits(const sf::Time& dt) {
    working -= dt.asMilliseconds();
    if (working <= 0) {
        working = GameConstants::instance().cFARM_TIME_CYCLE();
        return lvl_ * GameConstants::instance().cFARM_LVL_BENEFITS();
    }
    return 0;
}

int Farm::upgrade() {
    int minusGold = upgradeCost_;
    ++lvl_;
    upgradeCost_ = static_cast<int>(log2(GameConstants::instance().cFARM_INC_COST_BASE() + lvl_) *
                                    GameConstants::instance().cFARM_COST());
    return minusGold;
}
