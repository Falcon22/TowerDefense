#include "GraphicsBullet.h"

GraphicsBullet::GraphicsBullet(const Bullet* bullet, States::Context& context)
    : explosionTime_(0),
      finished_(false),
      bullet_(bullet) {
    switch (bullet->getType()) {
        case Type::lvlOne:
            sprite_.setTexture(context.textureHolder->get(Textures::bulletOne));
            break;
        case Type::lvlTwo:
            sprite_.setTexture(context.textureHolder->get(Textures::bulletTwo));
            explosion_.setTexture(context.textureHolder->get(Textures::explosion));
            explosion_.setOrigin(explosion_.getTextureRect().width / 2, explosion_.getTextureRect().height / 2);
            break;
    }
    sprite_.setOrigin(sprite_.getTextureRect().width / 2, sprite_.getTextureRect().height / 2);
}

void GraphicsBullet::update(const sf::Time& dTime) {
    if (explosionTime_ > 0) {
        explosionTime_ -= dTime.asMilliseconds();
        if (explosionTime_ == 0) {
            --explosionTime_;
        }
        return;
    } else if (explosionTime_ < 0) {
        finished_ = true;
        return;
    }
    if (!bullet_->isExploded() && !bullet_->isDisappeared()) {
        sprite_.setPosition(bullet_->getPosition());
        sprite_.setRotation(bullet_->getAngle());
    } else {
        explosionTime_ = 500;
    }

}

void GraphicsBullet::draw(States::Context& context) {
    if (finished_) {
        return;
    }
    if (explosionTime_ == 0) {
        context.window->draw(sprite_);
    } else {
        context.window->draw(explosion_);
    }
}

bool GraphicsBullet::isFinished() const {
    return finished_;
}
