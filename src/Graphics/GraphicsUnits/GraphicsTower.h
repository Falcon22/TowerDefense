#ifndef SERVER_GRAPHICSTOWER_H
#define SERVER_GRAPHICSTOWER_H


#include <SFML/Graphics/Sprite.hpp>
#include "../../GameContext.h"
#include "../../Units/Tower/Tower.h"

class GraphicsTower {
public:
    explicit GraphicsTower(States::Context& context);
    void draw(States::Context& context, const std::shared_ptr<Tower>& tower, int id);

private:
    sf::Sprite towerZeroRed_;
    sf::Sprite towerZeroBlue_;
    sf::Sprite towerTopLvlOne_;
    sf::Sprite towerBaseLvlOne_;
    sf::Sprite towerTopLvlTwo_;
    sf::Sprite towerBaseLvlTwo_;
    sf::Sprite towerTopLvlThree_;
    sf::Sprite towerBaseLvlThree_;

    const sf::Color red_ = sf::Color(255, 136, 138);
    const sf::Color blue_ = sf::Color(91, 171, 232);
};


#endif //SERVER_GRAPHICSTOWER_H
