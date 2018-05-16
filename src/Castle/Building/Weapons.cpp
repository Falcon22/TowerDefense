#include "Weapons.h"

Weapons::Weapons()
    : Building(GameConstants::instance().cWEAPONS_1_COST()) {
}

int Weapons::upgrade() {
    if (lvl_ >= 3) {
        return 0;
    }
    int minusGold = upgradeCost_;
    ++lvl_;
    if (lvl_ == 1) {
        upgradeCost_ = GameConstants::instance().cWEAPONS_2_COST();
    } else if (lvl_ == 2) {
        upgradeCost_ = GameConstants::instance().cWEAPONS_3_COST();
    }
    return minusGold;
}
