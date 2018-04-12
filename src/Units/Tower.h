#ifndef TEMPPROJECT_TOWER_H
#define TEMPPROJECT_TOWER_H


#include "UnitsComponents/GameUnit.h"

class Tower: public GameUnit {
public:
    Tower(InputComponent* input, GraphicsComponent* graphics, LogicComponent* logic);
};


#endif //TEMPPROJECT_TOWER_H
