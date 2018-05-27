#ifndef TOWERDEFENSE_WEAPONS_H
#define TOWERDEFENSE_WEAPONS_H


#include "Building.h"

class Weapons: public Building {
public:
    Weapons();

    int upgrade() override;
};


#endif //TOWERDEFENSE_WEAPONS_H
