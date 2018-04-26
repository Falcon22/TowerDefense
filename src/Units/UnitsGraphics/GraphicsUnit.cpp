#include "GraphicsUnit.h"

GraphicsUnit::GraphicsUnit(sf::RenderWindow &window, Type type, const TextureHolder& textureHolder) : window_(window){
    switch (type) {
        case Type::lvlOne:
            sprite_.setTexture(textureHolder.get(Textures::warriorLvlOne));
            break;
        case Type::lvlTwo:
            sprite_.setTexture(textureHolder.get(Textures::warriorLvlTwo));
            break;
    }
    currentFrame_ = 0;
    sprite_.setScale(0.5, 0.5);
    width_ = sprite_.getTextureRect().width / kFrames_;
    height_ = sprite_.getTextureRect().height;
    sprite_.setTextureRect(sf::IntRect(0, 0, width_, height_));
    sprite_.setOrigin(static_cast<float >(width_) / 2, static_cast<float >(height_) / 2);
}

void GraphicsUnit::update(Warrior &unit, const sf::Time &dTime) {
    sprite_.setRotation(unit.getDirection());
    sprite_.setPosition(unit.getPosition());
    currentFrame_ += kAnimationSpeed_ * dTime.asSeconds();
    if (currentFrame_ >= kFrames_)
        currentFrame_ -= kFrames_;
    sprite_.setTextureRect(sf::IntRect(width_ * static_cast<int>(currentFrame_), 0, width_, height_));
}
