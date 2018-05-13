#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include "GraphicsTower.h"

GraphicsTower::GraphicsTower(States::Context &context) {
    towerZero_.setTexture(context.textureHolder->get(Textures::towerZero));
    towerZero_.setOrigin(towerZero_.getTextureRect().width / 2, towerZero_.getTextureRect().height / 2);

    towerTopLvlOne_.setTexture(context.textureHolder->get(Textures::towerOneTop));
    towerTopLvlOne_.setOrigin(towerTopLvlOne_.getTextureRect().width / 2, towerTopLvlOne_.getTextureRect().height / 2);
    towerBaseLvlOne_.setTexture(context.textureHolder->get(Textures::towerOneBase));
    towerBaseLvlOne_.setOrigin(towerBaseLvlOne_.getTextureRect().width / 2, towerBaseLvlOne_.getTextureRect().height / 2);

    towerTopLvlTwo_.setTexture(context.textureHolder->get(Textures::towerTwoTop));
    towerTopLvlTwo_.setOrigin(towerTopLvlTwo_.getTextureRect().width / 2, towerTopLvlTwo_.getTextureRect().height / 2);
    towerBaseLvlTwo_.setTexture(context.textureHolder->get(Textures::towerTwoBase));
    towerBaseLvlTwo_.setOrigin(towerBaseLvlTwo_.getTextureRect().width / 2, towerBaseLvlTwo_.getTextureRect().height / 2);

    towerTopLvlThree_.setTexture(context.textureHolder->get(Textures::towerThreeTop));
    towerTopLvlThree_.setOrigin(towerTopLvlThree_.getTextureRect().width / 2, towerTopLvlThree_.getTextureRect().height / 2);
    towerBaseLvlThree_.setTexture(context.textureHolder->get(Textures::towerThreeBase));
    towerBaseLvlThree_.setOrigin(towerBaseLvlThree_.getTextureRect().width / 2, towerBaseLvlThree_.getTextureRect().height / 2);
}

void GraphicsTower::draw(States::Context& context, const std::shared_ptr<Tower>& tower) {
    if (tower == nullptr) {
        return;
    }
    switch (tower->getType()) {
        case Type::lvlZero:
            towerZero_.setPosition(tower->getPosition());
            context.window->draw(towerZero_);
            break;
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
        case Type::lvlThree:
            towerBaseLvlThree_.setPosition(tower->getPosition());
            towerTopLvlThree_.setPosition(tower->getPosition());
            towerTopLvlThree_.setRotation(tower->getAngle());
            context.window->draw(towerBaseLvlThree_);
            context.window->draw(towerTopLvlThree_);
            break;
    }
}