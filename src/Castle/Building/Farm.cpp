#include <iostream>
#include "Farm.h"

Farm::Farm()
    : Building(kCost_, kCost_),
      working(kWorkTime_) {
}

int Farm::getBenefits(const sf::Time& dt) {
    working -= dt.asMilliseconds();
    if (working <= 0) {
        working = kWorkTime_;
        switch (lvl_) {
            case Type::lvlOne:
                return kLvlBenefits_;
            case Type::lvlTwo:
                return kLvlBenefits_ * 2;
            case Type::lvlThree:
                return kLvlBenefits_ * 3;
        }
    }
    return 0;
}
