#include "GraphicsBullet.h"

GraphicsBullet::GraphicsBullet(std::shared_ptr<Bullet> bullet, States::Context& context)
        : explosionTime_(100),
          exploded_(false),
          finished_(false),
          bullet_(bullet) {
    switch (bullet->getType()) {
        case Type::lvlOne:
            sprite_.setTexture(context.textureHolder->get(Textures::bulletOne));
            explosion_.setTexture(context.textureHolder->get(Textures::explosionOne));
            explosion_.setScale({0.5, 0.5});
            break;
        case Type::lvlTwo:
            sprite_.setTexture(context.textureHolder->get(Textures::bulletTwo));
            sprite_.setScale({0.75, 0.75});
            explosion_.setTexture(context.textureHolder->get(Textures::explosionTwo));
            explosion_.setScale({0.75, 0.75});
            break;
        case Type::lvlThree:
            sprite_.setTexture(context.textureHolder->get(Textures::bulletThree));
            explosion_.setTexture(context.textureHolder->get(Textures::explosionThree));
            break;
    }
    sprite_.setOrigin(sprite_.getTextureRect().width / 2, sprite_.getTextureRect().height / 2);
    explosion_.setOrigin(explosion_.getTextureRect().width / 2, explosion_.getTextureRect().height / 2);
}

bool GraphicsBullet::update(const sf::Time& dTime) {
    if (bullet_ == nullptr) {
        return false;
    }
    if (bullet_->isDisappeared()) {
        finished_ = true;
        return true;
    }
    if (!exploded_) {
        if (bullet_->isExploded()) {
            exploded_ = true;
            explosion_.setPosition(bullet_->getPosition());
            return true;
        }
        sprite_.setPosition(bullet_->getPosition());
        sprite_.setRotation(static_cast<float>(-bullet_->getAngle() * 180 / M_PI + 180));
    } else {
        explosionTime_ -= dTime.asMilliseconds();
        if (explosionTime_ < 0) {
            finished_ = true;
        }
    }
    return false;
}

void GraphicsBullet::draw(States::Context& context) {
    if (!exploded_) {
        context.window->draw(sprite_);
    } else {
        context.window->draw(explosion_);
    }
}

bool GraphicsBullet::isFinished() const {
    return finished_;
}

bool GraphicsBullet::isExploded() const {
    return exploded_;
}
