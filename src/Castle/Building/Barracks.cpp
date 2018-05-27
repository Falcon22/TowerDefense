#include "Barracks.h"

Barracks::Barracks()
    : Building(GameConstants::instance().cBARRACKS_1_COST()) {
}

int Barracks::upgrade() {
    if (lvl_ >= 2) {
        return 0;
    }
    int minusGold = upgradeCost_;
    ++lvl_;
    if (lvl_ == 1) {
        upgradeCost_ = GameConstants::instance().cBARRACKS_2_COST();
    }

    return minusGold;
}
