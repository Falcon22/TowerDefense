#include "Building.h"

Building::Building(int upgradeCost)
    : upgradeCost_(upgradeCost),
      lvl_(0) {
}

unsigned char Building::getLvl() const {
    return lvl_;
}

int Building::getUpgradeCost() const {
    return upgradeCost_;
}
