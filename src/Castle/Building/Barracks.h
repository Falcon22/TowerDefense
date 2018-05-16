#ifndef TOWERDEFENSE_BARRACKS_H
#define TOWERDEFENSE_BARRACKS_H


#include "Building.h"

class Barracks: public Building {
public:
    Barracks();

    int upgrade() override;
};


#endif //TOWERDEFENSE_BARRACKS_H
