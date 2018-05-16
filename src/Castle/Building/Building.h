#ifndef TOWERDEFENSE_BUILDING_H
#define TOWERDEFENSE_BUILDING_H


#include "../../GameContext.h"
#include "../../GameConstants.h"

class Building {
public:
    virtual int upgrade() = 0;
    unsigned char getLvl() const;
    int getUpgradeCost() const;

protected:
    explicit Building(int upgradeCost);

    int upgradeCost_;
    unsigned char lvl_;
};


#endif //TOWERDEFENSE_BUILDING_H
