#include "Bullet.h"
#include <cmath>

Bullet::Bullet(Type type, const sf::Vector2f& position, Warrior& target, int damage, float velocity,
               float angle)
    : GameUnit(type, position),
      target_(target),
      damage_(damage),
      velocity_(velocity),
      angle_(angle),
      exploded_(false),
      disappeared_(false) {
}

void Bullet::update(const sf::Time& dTime) {
    if (!exploded_ && target_.isAlive()) {
        if (!checkCollisionWithTarget()) {
            angle_ = static_cast<float>(atan2((target_.getPosition().x - position_.x), (target_.getPosition().y - position_.y)));
            position_.x += velocity_ * dTime.asSeconds() * sin(angle_);
            position_.y += velocity_ * dTime.asSeconds() * cos(angle_);
        } else {
            exploded_ = true;
            damage();
        }
    } else {
        if (!target_.isAlive()) {
            disappeared_ = true;
        }
    }
}

bool Bullet::checkCollisionWithTarget() {
    float area = 20;
    return (position_.x < target_.getPosition().x + area && position_.x > target_.getPosition().x - area)
           && (position_.y < target_.getPosition().y + area && position_.y > target_.getPosition().y - area);
}

void Bullet::damage() {
    target_.suffer(damage_);
}

float Bullet::getAngle() const {
    return angle_;
}

bool Bullet::isExploded() const {
    return exploded_ || disappeared_;
}

bool Bullet::isDisappeared() const {
    return disappeared_;
}
