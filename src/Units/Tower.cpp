#include "Tower.h"
#include "UnitsComponents/InputComponents/TowerInputComponent.h"
#include "UnitsComponents/GraphicsComponents/TowerGraphicsComponent.h"
#include "UnitsComponents/LogicComponents/TowerLogicComponent.h"

Tower::Tower(InputComponent *input, GraphicsComponent *graphics, LogicComponent *logic)
    : GameUnit(new TowerInputComponent, new TowerGraphicsComponent, new TowerLogicComponent) {}
