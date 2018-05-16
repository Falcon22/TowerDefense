#include "LogicUnitsManager.h"
#include "../Castle/Castle.h"
#include "Bullet/Bullet.h"

LogicUnitsManager::LogicUnitsManager()
    : player1_(std::make_shared<Castle>()),
      player2_(std::make_shared<Castle>()) {
    std::cout << "LComponentConstructor" << std::endl;
    player1_->setEnemy(player2_);
    player2_->setEnemy(player1_);
}

void LogicUnitsManager::update(const sf::Time& dTime) {
    player1_->updateCastle(dTime);
    player2_->updateCastle(dTime);

    updateBullets(dTime);
}

void LogicUnitsManager::updateBullets(const sf::Time& dTime) {
    for (auto bullet = bullets_.begin(); bullet != bullets_.end();) {
        (*bullet)->update(dTime);
        if (*bullet == nullptr || (*bullet)->isExploded() || (*bullet)->isDisappeared()) {
            bullet = bullets_.erase(bullet);
        } else {
            ++bullet;
        }
    }
}

std::shared_ptr<Castle> &LogicUnitsManager::getPlayer1() {
    return player1_;
}

std::shared_ptr<Castle> &LogicUnitsManager::getPlayer2() {
    return player2_;
}

std::vector<std::shared_ptr<Bullet>> &LogicUnitsManager::getBullets() {
    return bullets_;
}

