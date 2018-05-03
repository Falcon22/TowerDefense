#ifndef TOWERDEFENSE_WEAPONS_H
#define TOWERDEFENSE_WEAPONS_H


#include "Building.h"

class Weapons: public Building {
public:
    Weapons();

private:
    static const int kCost_ = 1000;
};


#endif //TOWERDEFENSE_WEAPONS_H
