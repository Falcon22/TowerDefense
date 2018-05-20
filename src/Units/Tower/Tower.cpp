#include <cmath>
#include  <valarray>
#include "Tower.h"
#include "../Warrior/Warrior.h"
#include "TowerLvlOne.h"
#include "TowerLvlTwo.h"
#include "TowerLvlThree.h"

#define RAD_IN_DEGREE (180 / M_PI)

Tower::Tower(Type type, const sf::Vector2f& position, unsigned int price, float attackRange, float attackCooldown,
             std::list<std::shared_ptr<Warrior>>& warriors, std::vector<std::shared_ptr<Bullet>>& bullets)
        : GameUnit(type, position),
          price_(price),
          angle_(0),
          attackRange_(attackRange),
          attackCooldown_(attackCooldown),
          warriors_(warriors),
          bullets_(bullets),
          target_(nullptr),
          cooldown_(0) {}

void Tower::update(const sf::Time& dTime) {
    if (target_ != nullptr) {
        if (inRange(target_->getPosition()) && target_->isAlive() && !target_->isFinished()) {
            angle_ = aim();
            shoot(dTime);
        } else {
            target_.reset();
        }
    } else {
        for (const auto& warrior : warriors_) {
            if (warrior != nullptr && inRange(warrior->getPosition()) && warrior->isAlive() && !warrior->isFinished()) {
                target_ = warrior;
                break;
            }
        }
    }
}

unsigned int Tower::getPrice() {
    return price_;
}

bool Tower::inRange(const sf::Vector2f& pointPosition) const {
    return (pointPosition.x - position_.x) * (pointPosition.x - position_.x)
           + (pointPosition.y - position_.y) * (pointPosition.y - position_.y) <= attackRange_ * attackRange_;
}

float Tower::aim() const {
    return static_cast<float>((std::atan2((position_.y - target_->getPosition().y),
                                     (position_.x - target_->getPosition().x)) * RAD_IN_DEGREE) - 90);
}

void Tower::shoot(const sf::Time &dTime) {
    cooldown_ -= dTime.asSeconds();
    if (cooldown_ < 0) {
        cooldown_ = attackCooldown_;
        bullets_.emplace_back(makeBullet());
    }
}

float Tower::getAngle() const {
    return angle_;
}

int Tower::upgrade(std::shared_ptr<Tower>& tower) {
    switch (tower->type_) {
        case Type ::lvlZero:
            tower.reset(new TowerLvlOne(tower->position_, tower->warriors_, tower->bullets_));
            break;
        case Type::lvlOne:
            tower.reset(new TowerLvlTwo(tower->position_, tower->warriors_, tower->bullets_));
            break;
        case Type::lvlTwo:
            tower.reset(new TowerLvlThree(tower->position_, tower->warriors_, tower->bullets_));
            break;
        default:
            return 0;
    }
    return tower->getPrice();
}