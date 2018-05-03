#ifndef TOWERDEFENSE_BUILDING_H
#define TOWERDEFENSE_BUILDING_H


#include "../../GameContext.h"

class Building {
public:
    void upgrade();
    Type getLvl() const;
    int getUpgradeCost() const;

protected:
    Building(int upgradeCost, int costIncrement);

    int upgradeCost_;
    int costIncrement_;
    Type lvl_;
};


#endif //TOWERDEFENSE_BUILDING_H
