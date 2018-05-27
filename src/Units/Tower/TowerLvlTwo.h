#ifndef TOWERDEFENSE_TOWERLVLTWO_H
#define TOWERDEFENSE_TOWERLVLTWO_H


#include "Tower.h"
#include "../../Constants.h"

class TowerLvlTwo: public Tower {
public:
    TowerLvlTwo(const sf::Vector2f& position, std::list<std::shared_ptr<Warrior>>& warriors, std::vector<std::shared_ptr<Bullet>>& bullets);

    std::shared_ptr<Bullet> makeBullet() override;
};



#endif //TOWERDEFENSE_TOWERLVLTWO_H