#include "Building.h"

Building::Building(int upgradeCost, int costIncrement)
    : upgradeCost_(upgradeCost),
      costIncrement_(costIncrement),
      lvl_(Type::lvlOne) {
}

void Building::upgrade() {
    upgradeCost_ += costIncrement_;
    switch (lvl_) {
        case Type::lvlOne:
            lvl_ = Type::lvlTwo;
            break;
        case Type::lvlTwo:
            lvl_ = Type::lvlThree;
            upgradeCost_ = 999999999;
            break;
        case Type::lvlThree:
            break;
    }
}

Type Building::getLvl() const {
    return lvl_;
}

int Building::getUpgradeCost() const {
    return upgradeCost_;
}
