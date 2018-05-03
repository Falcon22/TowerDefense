#ifndef TOWERDEFENSE_GRAPHICSTOWER_H
#define TOWERDEFENSE_GRAPHICSTOWER_H


#include <SFML/Graphics/Sprite.hpp>
#include "../../GameContext.h"
#include "../../Units/Tower/Tower.h"

class GraphicsTower {
public:
    explicit GraphicsTower(States::Context& context);
    void draw(States::Context& context, const Tower* tower);

private:
    sf::Sprite towerTopLvlOne_;
    sf::Sprite towerBaseLvlOne_;
    sf::Sprite towerTopLvlTwo_;
    sf::Sprite towerBaseLvlTwo_;
};


#endif //TOWERDEFENSE_GRAPHICSTOWER_H
