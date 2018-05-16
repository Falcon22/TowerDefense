#include <SFML/Graphics/RenderWindow.hpp>
#include <utility>
#include "GraphicsWarrior.h"

GraphicsWarrior::GraphicsWarrior(std::shared_ptr<Warrior>& warrior, States::Context& context)
        : warrior_(warrior),
          deathDuration_(2000),
          finishedDuration_(200),
          died_(false),
          finishing_(false),
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
    explosionSprite_.setTexture(context.textureHolder->get(Textures::warriorExplosion));
    explosionSprite_.setOrigin(deadSprite_.getTextureRect().width / 2, deadSprite_.getTextureRect().height / 2);
}

void GraphicsWarrior::update(const sf::Time& dTime) {
    if (!finishing_ && !died_ && warrior_ != nullptr) {
        if (!warrior_->isAlive()) {
            deadSprite_.setPosition(warrior_->getPosition());
            died_ = true;
            warrior_.reset();
            return;
        }
        if (warrior_->isFinished()) {
            explosionSprite_.setPosition(warrior_->getPosition());
            if (warrior_.get()->getType() == Type::lvlTwo) {
                explosionSprite_.setScale({1.5, 1.5});
            }
            finishing_ = true;
            warrior_.reset();
            return;
        }
        lifeAnimation(dTime);
    } else if (died_) {
        deathAnimation(dTime);
    } else {
        finishedAnimation(dTime);
    }

}

void GraphicsWarrior::draw(const States::Context& context) {
    if (died_) {
        context.window->draw(deadSprite_);
    } else if (finishing_) {
        context.window->draw(explosionSprite_);
    } else {
        context.window->draw(sprite_);
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
    deathDuration_ -= dTime.asMilliseconds();
    if (deathDuration_ <= 0) {
        finished_ = true;
        return;
    }
}

bool GraphicsWarrior::isDied() const {
    return died_;
}

void GraphicsWarrior::finishedAnimation(const sf::Time &dTime) {
    finishedDuration_ -= dTime.asMilliseconds();
    if (finishedDuration_ <= 0) {
        finished_ = true;
        return;
    }
}
