#ifndef TEMPPROJECT_GAMEUNIT_H
#define TEMPPROJECT_GAMEUNIT_H


#include "InputComponents/InputComponent.h"
#include "LogicComponents/LogicComponent.h"
#include "GraphicsComponents/GraphicsComponent.h"

class GameUnit {
public:
    GameUnit(InputComponent* input, GraphicsComponent* graphics, LogicComponent* logic);
    virtual ~GameUnit() = default;

    void Update();

    //Some public data for all units (like (x, y))

private:
    InputComponent* input_;
    LogicComponent* logic_;
    GraphicsComponent* graphics_;
};


#endif //TEMPPROJECT_GAMEUNIT_H
