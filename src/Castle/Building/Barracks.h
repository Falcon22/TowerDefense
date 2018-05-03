#ifndef TOWERDEFENSE_BARRACKS_H
#define TOWERDEFENSE_BARRACKS_H


#include "Building.h"

class Barracks: public Building {
public:
    Barracks();

private:
    static const int kCost_ = 1000;
};


#endif //TOWERDEFENSE_BARRACKS_H
