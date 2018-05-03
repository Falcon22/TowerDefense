#include  <valarray>
#include "Tower.h"
#include "../Warrior/Warrior.h"
#include "TowerLvlOne.h"
#include "TowerLvlTwo.h"
#include "TowerLvlThree.h"
#include "../../Graphics/GraphicsUnit/GraphicsBullet.h"


Tower::Tower(Type type, const sf::Vector2f& position, unsigned int price, float attackRange, float attackCooldown,
             std::list<Warrior*>& warriors, std::vector<Bullet*>& bullets)
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
        if (inRange(target_->getPosition()) && target_->isAlive()) {
            angle_ = aim();
            shoot(dTime);
        } else {
            target_ = nullptr;
        }
    } else {
        for (auto warrior : warriors_) {
            if (inRange(warrior->getPosition()) && warrior->isAlive()) {
                target_ = warrior;////
                break;
            }
        }
    }

}

bool Tower::inRange(const sf::Vector2f& pointPosition) const {
    return (pointPosition.x - position_.x) * (pointPosition.x - position_.x)
           + (pointPosition.y - position_.y) * (pointPosition.y - position_.y) <= attackRange_ * attackRange_;
}

float Tower::aim() const {
    return static_cast<float>((atan2((position_.y - target_->getPosition().y),
                                      (position_.x - target_->getPosition().x)) * 180 / M_PI) - 90);
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

void Tower::upgrade(Tower*& tower) {
    Tower* newTower = nullptr;
    switch (tower->type_) {
        case Type ::lvlZero:
            newTower = new TowerLvlOne(tower->position_, tower->warriors_, tower->bullets_);
            delete tower;
            tower = newTower;
            break;
        case Type::lvlOne:
            newTower = new TowerLvlTwo(tower->position_, tower->warriors_, tower->bullets_);
            delete tower;
            tower = newTower;
            break;
        case Type::lvlTwo:
            newTower = new TowerLvlThree(tower->position_, tower->warriors_, tower->bullets_);
            delete tower;
            tower = newTower;
            break;
        default:
            break;
    }
}
