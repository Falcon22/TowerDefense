#ifndef TOWERDEFENSE_FARM_H
#define TOWERDEFENSE_FARM_H


#include <SFML/System/Time.hpp>
#include "Building.h"

class Farm: public Building {
public:
    Farm();
    int getBenefits(const sf::Time& dt);
    int upgrade() override;

private:
    sf::Int32 working;
};


#endif //TOWERDEFENSE_FARM_H
