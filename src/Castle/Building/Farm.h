#ifndef TOWERDEFENSE_FARM_H
#define TOWERDEFENSE_FARM_H


#include <SFML/System/Time.hpp>
#include "Building.h"

class Farm: public Building {
public:
    Farm();
    int getBenefits(const sf::Time& dt);

private:
    sf::Int32 working;

    static const int kCost_ = 1000;
    static const int kLvlBenefits_ = 100;
    static const sf::Int32 kWorkTime_ = 10000;//mseconds
};


#endif //TOWERDEFENSE_FARM_H
