#include <SFML/Graphics/RenderWindow.hpp>
#include "GraphicsWarrior.h"

GraphicsWarrior::GraphicsWarrior(const Warrior* warrior, States::Context& context)
        : warrior_(warrior),
          finished_(false) {
    switch (warrior_->getType()) {
        case Type::lvlOne:
            sprite_.setTexture(context.textureHolder->get(Textures::warriorLvlOne));
            break;
        case Type::lvlTwo:
            sprite_.setTextureRect(sf::IntRect(0, 0, warriorSpriteRect_.first, warriorSpriteRect_.second));
            break;
    }
    sprite_.setScale({0.5, 0.5});
    warriorSpriteRect_.first = sprite_.getTextureRect().width / 4;
    warriorSpriteRect_.second = sprite_.getTextureRect().height;
    sprite_.setTextureRect(sf::IntRect(0, 0, warriorSpriteRect_.first, warriorSpriteRect_.second));
    sprite_.setOrigin(warriorSpriteRect_.first / 2, warriorSpriteRect_.second / 2);

}

void GraphicsWarrior::update(const sf::Time& dTime) {
    if (!warrior_->isAlive() || warrior_->isFinished()) {
        finished_ = true;
    }
    currentFrame_ += 10 * dTime.asSeconds();
    if (currentFrame_ >= 4)
        currentFrame_ -= 4;
    sprite_.setTextureRect(sf::IntRect(warriorSpriteRect_.first * static_cast<int>(currentFrame_), 0,
                                       warriorSpriteRect_.first, warriorSpriteRect_.second));
    sprite_.setPosition(warrior_->getPosition());
    sprite_.setRotation(warrior_->getDirection());
}

void GraphicsWarrior::draw(const States::Context& context) {
    context.window->draw(sprite_);
}

bool GraphicsWarrior::isFinished() const {
    return finished_;
}
