#include <SFML/Graphics/RenderWindow.hpp>
#include "GraphicsTower.h"

GraphicsTower::GraphicsTower(States::Context &context) {
    towerTopLvlOne_.setTexture(context.textureHolder->get(Textures::towerTopLvlOne));
    towerTopLvlOne_.setOrigin(towerTopLvlOne_.getTextureRect().width / 2, towerTopLvlOne_.getTextureRect().height / 2);
    towerBaseLvlOne_.setTexture(context.textureHolder->get(Textures::towerBaseLvlOne));
    towerBaseLvlOne_.setOrigin(towerBaseLvlOne_.getTextureRect().width / 2, towerBaseLvlOne_.getTextureRect().height / 2);
    towerTopLvlTwo_.setTexture(context.textureHolder->get(Textures::towerTopLvlTwo));
    towerTopLvlTwo_.setOrigin(towerTopLvlTwo_.getTextureRect().width / 2, towerTopLvlTwo_.getTextureRect().height / 2);
    towerBaseLvlTwo_.setTexture(context.textureHolder->get(Textures::towerBaseLvlTwo));
    towerBaseLvlTwo_.setOrigin(towerBaseLvlTwo_.getTextureRect().width / 2, towerBaseLvlTwo_.getTextureRect().height / 2);
}

void GraphicsTower::draw(States::Context& context, const Tower* tower) {
    switch (tower->getType()) {
        case Type::lvlOne:
            towerBaseLvlOne_.setPosition(tower->getPosition());
            towerTopLvlOne_.setPosition(tower->getPosition());
            towerTopLvlOne_.setRotation(tower->getAngle());
            context.window->draw(towerBaseLvlOne_);
            context.window->draw(towerTopLvlOne_);
            break;
        case Type::lvlTwo:
            towerBaseLvlTwo_.setPosition(tower->getPosition());
            towerTopLvlTwo_.setPosition(tower->getPosition());
            towerTopLvlTwo_.setRotation(tower->getAngle());
            context.window->draw(towerBaseLvlTwo_);
            context.window->draw(towerTopLvlTwo_);
            break;
    }
}
