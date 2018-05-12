#include <SFML/Graphics/RenderWindow.hpp>
#include "GraphicsWarrior.h"

GraphicsWarrior::GraphicsWarrior(const Warrior* warrior, States::Context& context)
        : warrior_(warrior),
          deathDuration(2000),
          died_(false),
          finished_(false) {
    switch (warrior_->getType()) {
        case Type::lvlOne:
            sprite_.setTexture(context.textureHolder->get(Textures::warriorOne));
            break;
        case Type::lvlTwo:
            sprite_.setTexture(context.textureHolder->get(Textures::warriorTwo));
            break;
    }
    sprite_.setScale({0.5, 0.5});
    warriorSpriteRect_.first = sprite_.getTextureRect().width / kFrames_;
    warriorSpriteRect_.second = sprite_.getTextureRect().height;
    sprite_.setTextureRect(sf::IntRect(0, 0, warriorSpriteRect_.first, warriorSpriteRect_.second));
    sprite_.setOrigin(warriorSpriteRect_.first / 2, warriorSpriteRect_.second / 2);
    deadSprite_.setTexture(context.textureHolder->get(Textures::blood));
    deadSprite_.setOrigin(deadSprite_.getTextureRect().width / 2, deadSprite_.getTextureRect().height / 2);
}

void GraphicsWarrior::update(const sf::Time& dTime) {
    if (!died_ && !finished_ && warrior_ != nullptr) {
        lifeAnimation(dTime);
        if (!warrior_->isAlive()) {
            deadSprite_.setPosition(warrior_->getPosition());
            died_ = true;
            warrior_ = nullptr;
            return;
        }
        if (warrior_->isFinished()) {
            finished_ = true;
            warrior_ = nullptr;
            return;
        }
    } else if (!finished_) {
        deathAnimation(dTime);
    }

}

void GraphicsWarrior::draw(const States::Context& context) {
    if (!died_) {
        context.window->draw(sprite_);
    } else {
        context.window->draw(deadSprite_);
    }
}

bool GraphicsWarrior::isFinished() const {
    return finished_;
}

void GraphicsWarrior::lifeAnimation(const sf::Time& dTime) {
    currentFrame_ += 10 * dTime.asSeconds();
    if (currentFrame_ >= kFrames_)
        currentFrame_ -= kFrames_;
    sprite_.setTextureRect(sf::IntRect(warriorSpriteRect_.first * static_cast<int>(currentFrame_), 0,
                                       warriorSpriteRect_.first, warriorSpriteRect_.second));
    sprite_.setPosition(warrior_->getPosition());
    sprite_.setRotation(warrior_->getDirection());
}

void GraphicsWarrior::deathAnimation(const sf::Time& dTime) {
    deathDuration -= dTime.asMilliseconds();
    if (deathDuration <= 0) {
        finished_ = true;
        return;
    }
    //сюда бы постепенную прозрачность
}

bool GraphicsWarrior::isDied() const {
    return died_;
}
