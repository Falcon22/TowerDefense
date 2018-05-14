#ifndef SERVER_GRAPHICSTOWER_H
#define SERVER_GRAPHICSTOWER_H


#include <SFML/Graphics/Sprite.hpp>
#include "../../GameContext.h"
#include "../../Units/Tower/Tower.h"

class GraphicsTower {
public:
    explicit GraphicsTower(States::Context& context);
    void draw(States::Context& context, const std::shared_ptr<Tower>& tower);

private:
    sf::Sprite towerZero_;
    sf::Sprite towerTopLvlOne_;
    sf::Sprite towerBaseLvlOne_;
    sf::Sprite towerTopLvlTwo_;
    sf::Sprite towerBaseLvlTwo_;
    sf::Sprite towerTopLvlThree_;
    sf::Sprite towerBaseLvlThree_;
};


#endif //SERVER_GRAPHICSTOWER_H
